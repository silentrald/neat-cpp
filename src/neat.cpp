#include "neat.hpp"

Neat::Neat(int input, int output, int population) {
  init(input, output, population);
}

void Neat::init(int input, int output, int population) {
  Parameter::input = input;
  Parameter::output = output;
  Parameter::population = population;

  Organism::set_innovation(&this->innovation);

  // Create init nodes
  // Input nodes
  for (int i = 0; i < input; i++) {
    this->innovation.create_node(gene_type::INPUT);
  }

  // Output node
  for (int i = 0; i < output; i++) {
    this->innovation.create_node(gene_type::OUTPUT);
  }

  // There is always 1 bias node
  this->innovation.create_node(gene_type::BIAS);

  // Create init connections
  Gene* input_node;
  int innov = 0;
  for (int i = 0; i < input; i++) {
    input_node = this->innovation.get_node(i);
    for (int o = 0; o < output; o++) {
      this->innovation.create_connection(input_node, this->innovation.get_node(input + o));
    }
  }

  // Create the first generation species
  Genome* genome;
  Connection* connection;
  int connection_size = this->innovation.get_connections_size();
  for (int i = 0; i < population; i++) {
    genome = new Genome();
    for (auto it = this->innovation.get_nodes_begin(); it != this->innovation.get_nodes_end(); it++) {
      genome->add_node(*it);
    }

    // Select a random connection and add to the genome
    connection = new Connection(this->innovation.get_random_connection());
    connection->enabled = true;                                    // Already enabled but just to be safe
    connection->weight = (decimal)(Function::randf() * 2.0 - 1.0); // Randomized the weight
    genome->add_connection(connection);

    this->organisms.push_back(new Organism(genome));
  }
}

void Neat::_speciation() {
  Species* s = NULL;
  bool inserted = false;
  for (auto org = this->organisms.begin(); org != this->organisms.end(); org++) {
    inserted = false;
    for (auto sp = this->species.begin(); sp != this->species.end(); sp++) {
      if ((*sp)->compare_candidate(*org) < Parameter::compatibility_threshold) {
        (*sp)->add_organism(*org);
        inserted = true;
        break;
      }
    }

    if (inserted)
      continue;

    // Create new species
    s = new Species(*org);
    s->innov = this->species.size();
    this->species.push_back(s);
  }
  this->organisms.clear();
}

void Neat::_extinction() {
  // Kill the least amount of fitness in each species
  for (auto sp = this->species.begin(); sp != this->species.end(); sp++) {
    (*sp)->kill_organism(Parameter::survival_threshold);
  }
}

void Neat::_reproduction() {
  // Filter species if species is have organism
  std::vector<Species*> filtered_species;
  for (auto sp = this->species.begin(); sp != this->species.end(); sp++) {
    if ((*sp)->organism_size() > 0)
      filtered_species.push_back((*sp));
  }

  decimal total_fitness = 0.0;
  for (auto sp = filtered_species.begin(); sp != filtered_species.end(); sp++) {
    total_fitness += (*sp)->total_fitness;
  }

  decimal fraction = 0.0;
  for (auto sp = filtered_species.begin(); sp != filtered_species.end(); sp++) {
    fraction = (*sp)->reproduce(this->organisms, filtered_species, total_fitness, fraction);
  }
}

void Neat::_cleanup() {
  for (auto sp = this->species.begin(); sp != this->species.end(); sp++) {
    (*sp)->clear_organism();
  }
}

void Neat::create_next_generation() {
  this->_speciation();
  this->_extinction();
  this->_reproduction();
  this->_cleanup();
}

Neat::~Neat() {
  for (auto it = this->organisms.begin(); it != this->organisms.end(); it++) {
    delete *it;
  }
  this->organisms.clear();
}
