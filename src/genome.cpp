#include "genome.hpp"

Genome::Genome() {}

Genome::Genome(Genome* other) {
  for (auto it = other->node_genes.begin(); it != other->node_genes.end(); it++) {
    this->node_genes[it->first] = it->second;
  }

  for (auto it = other->connection_genes.begin(); it != other->connection_genes.end(); it++) {
    this->connection_genes[it->first] = new Connection(it->second);
  }
}

Genome::~Genome() {
  this->node_genes.clear();
  for (auto it = this->connection_genes.begin(); it != this->connection_genes.end(); it++) {
    delete it->second;
  }
  this->connection_genes.clear();
}

void Genome::add_node(Gene* node) {
  this->node_genes[node->innov] = node;
}

void Genome::add_connection(Connection* connection) {
  this->connection_genes[connection->innov] = connection;
}

decimal Genome::calculate_distance(Genome* other) {
  decimal weight = 0.0;
  int disjoint = 0, excess = this->connection_genes.size() + other->connection_genes.size();
  std::unordered_map<int, Connection*>::iterator itc1 = this->connection_genes.begin();
  std::unordered_map<int, Connection*>::iterator itc2 = other->connection_genes.begin();
  Connection *c1, *c2;

  while (itc1 != this->connection_genes.end() && itc2 != other->connection_genes.end()) {
    c1 = itc1->second;
    c2 = itc2->second;

    // clang-format off
    if (c1->innov == c2->innov) {
      weight += abs(c1->weight - c2->weight);
      excess -= 2;
      itc1++; itc2++;
    } else if (c1->innov < c2->innov) {
      disjoint++; excess--;
      itc1++;
    } else {
      disjoint++; excess--;
      itc2++;
    }
    // clang-format on
  }

  int size = Function::max(this->node_genes.size(), other->node_genes.size());
  if (size < 20)
    size = 1;

  // (c1 * D / N) + (c2 * E / N) + c3 * W
  return Parameter::disjoint_coefficient * (decimal)disjoint / (decimal)size +
         Parameter::excess_coefficient * (decimal)excess / (decimal)size + Parameter::weight_diff_coefficient * weight;
}

Genome* Genome::crossover(Genome* other) {
  Genome* child = new Genome();

  // Add all node genes from both parents
  std::unordered_map<int, Gene*>::iterator itg1 = this->node_genes.begin();
  std::unordered_map<int, Gene*>::iterator itg2 = other->node_genes.begin();
  Gene *g1, *g2;
  while (itg1 != this->node_genes.end() && itg2 != other->node_genes.end()) {
    g1 = itg1->second;
    g2 = itg2->second;

    if (g1->innov == g2->innov) {
      child->add_node(g1);
      itg1++;
      itg2++;
    } else if (g1->innov < g2->innov) {
      child->add_node(g1);
      itg1++;
    } else {
      child->add_node(g2);
      itg2++;
    }
  }

  while (itg1 != this->node_genes.end()) {
    child->add_node(itg1->second);
    itg1++;
  }

  while (itg2 != other->node_genes.end()) {
    child->add_node(itg2->second);
    itg2++;
  }

  // Crossover the connections
  std::unordered_map<int, Connection*>::iterator itc1 = this->connection_genes.begin();
  std::unordered_map<int, Connection*>::iterator itc2 = other->connection_genes.begin();
  Connection *c1, *c2;
  while (itc1 != this->connection_genes.end() && itc2 != other->connection_genes.end()) {
    c1 = itc1->second;
    c2 = itc2->second;

    if (c1->innov == c2->innov) {
      c1 = new Connection(c1);
      c1->weight = Function::randf() < 0.5 ? c1->weight : c2->weight;
      c1->enabled = c1->enabled && c2->enabled;
      child->add_connection(c1);
      itc1++;
      itc2++;
    } else if (c1->innov < c2->innov) {
      child->add_connection(new Connection(c1));
      itc1++;
    } else {
      child->add_connection(new Connection(c2));
      itc2++;
    }
  }

  while (itc1 != this->connection_genes.end()) {
    child->add_connection(new Connection(itc1->second));
    itc1++;
  }

  while (itc2 != other->connection_genes.end()) {
    child->add_connection(new Connection(itc2->second));
    itc2++;
  }

  return child;
}

std::string Genome::to_string() {
  std::string str = "Node Genes\n";
  for (auto it = this->node_genes.begin(); it != this->node_genes.end(); it++) {
    str += it->second->to_string() + "\n";
  }
  str += "Connection Genes\n";
  for (auto it = this->connection_genes.begin(); it != this->connection_genes.end(); it++) {
    str += it->second->to_string() + "\n";
  }
  return str;
}
