#include "organism.hpp"

Innovation* Organism::innovation = NULL;

Organism::Organism() {}

Organism::Organism(Genome* genome) {
  this->genotype = genome;
  this->phenotype = new Network(genome);
}

Organism::Organism(Organism* org) {
  this->genotype = new Genome(org->genotype);
  this->phenotype = new Network(org->genotype);
}

Organism::~Organism() {
  delete this->genotype;
  delete this->phenotype;
}

void Organism::set_innovation(Innovation* innovation) {
  Organism::innovation = innovation;
}

std::vector<decimal> Organism::forward(const std::vector<decimal>& input) {
  return this->phenotype->forward(input);
}

decimal Organism::calculate_distance(Organism* org) {
  return this->genotype->calculate_distance(org->genotype);
}

Organism* Organism::breed(Organism* org) {
  return new Organism(this->genotype->crossover(org->genotype));
}

// Mutations
void Organism::mutate() {
  if (Function::randf() < Parameter::add_node_probability) {
    this->_mutate_add_node();
  }

  if (Function::randf() < Parameter::add_connection_probability) {
    this->_mutate_add_connection();
  }

  // For every connection
  for (auto it = this->genotype->connection_genes.begin(); it != this->genotype->connection_genes.end(); it++) {
    if (Function::randf() < Parameter::adjust_weight_probability) {
      this->_mutate_adjust_weight(it->second);
    } else if (Function::randf() < Parameter::randomized_weight_probability) {
      this->_mutate_randomized_weight(it->second);
    }

    if (Function::randf() < Parameter::toggle_link_probability) {
      this->_mutate_toggle_link(it->second);
    }
  }
}

void Organism::_mutate_add_connection() {
  // Create a pool of nodes
  std::vector<Gene*> input;
  std::vector<Gene*> output;

  Gene *g1 = NULL, *g2 = NULL;
  for (auto it = this->genotype->node_genes.begin(); it != this->genotype->node_genes.end(); it++) {
    g1 = it->second;
    switch (g1->type) {
    case gene_type::INPUT:
    case gene_type::BIAS:
      input.push_back(g1);
      break;
    case gene_type::OUTPUT:
      output.push_back(g1);
      break;
    case gene_type::HIDDEN:
      input.push_back(g1);
      output.push_back(g1);
      break;
    }
  }

  std::random_shuffle(input.begin(), input.end());
  std::random_shuffle(output.begin(), output.end());

  Connection* connection = new Connection(NULL, NULL, 0.0, true, 0);
  for (auto in = input.begin(); in != input.end(); in++) {
    for (auto out = output.begin(); out != output.end(); out++) {
      if (*in == *out)
        continue;

      // printf("In: %p\nOut: %p\n", *in, *out);

      connection->in = *in;
      connection->out = *out;

      if (!this->phenotype->is_cyclic_with_connection(connection)) {
        g1 = *in;
        g2 = *out;
        break;
      }
    }
  }

  // Cannot add
  if (g1 == NULL) {
    return;
  }

  // Check if the connection already exists
  connection = this->innovation->get_connection(g1->innov, g2->innov);
  if (connection == NULL)
    connection = this->innovation->create_connection(g1, g2);
  connection = new Connection(connection);
  connection->weight = Function::randf() * 2.0 - 1.0;
  this->_add_connection(connection);
}

void Organism::_mutate_add_node() {
  // Select a connection and split it in two
  Connection* connection = NULL;

  std::vector<int> connection_innovs;
  for (auto it = this->genotype->connection_genes.begin(); it != this->genotype->connection_genes.end(); it++) {
    if (it->second->in->type != gene_type::BIAS)
      connection_innovs.push_back(it->second->innov);
  }
  std::random_shuffle(connection_innovs.begin(), connection_innovs.end());

  for (auto it = connection_innovs.begin(); it != connection_innovs.end(); it++) {
    connection = this->innovation->get_connection(*it);

    // Check if the pair number is in the genome
    if (connection->in_con == NULL ||
        this->genotype->node_genes.find(connection->in_con->innov) == this->genotype->node_genes.end())
      break;
  }

  Gene* node;
  Connection *in_con, *out_con;
  if (connection->in_con == NULL) {
    node = this->innovation->create_node(gene_type::HIDDEN);

    // Create and edit the global connection innovation
    in_con = this->innovation->create_connection(connection->in, node);
    out_con = this->innovation->create_connection(node, connection->out);
    connection->in_con = in_con;
    connection->out_con = out_con;

    // Create a new connections for the genome
    in_con = new Connection(in_con);
    out_con = new Connection(out_con);
  } else {
    in_con = new Connection(connection->in_con);
    out_con = new Connection(connection->out_con);
    node = in_con->out;
  }

  // Get previous weight from the original connection
  in_con->weight = this->genotype->connection_genes[connection->innov]->weight;
  // Randomized the next connection
  out_con->weight = Function::randf() * 2.0 - 1.0;

  this->_add_node(node);
  this->_add_connection(in_con);
  this->_add_connection(out_con);
}

void Organism::_mutate_randomized_weight(Connection* connection) {
  connection->weight = Function::randf() * 2.0 - 1.0;
}

void Organism::_mutate_adjust_weight(Connection* connection) {
  connection->weight += (Function::randf() - 0.5) * 0.1;
  connection->weight = Function::clampf(connection->weight, -1.0, 1.0);
}

void Organism::_mutate_toggle_link(Connection* connection) {
  if (connection->enabled) {
    connection->enabled = false;
    return;
  }

  connection->enabled = !this->phenotype->is_cyclic_with_connection(connection);
}

void Organism::_add_node(Gene* node) {
  this->genotype->add_node(node);
}

void Organism::_add_connection(Connection* connection) {
  this->genotype->add_connection(connection);
  this->phenotype->add_connection(connection);
}