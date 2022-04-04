#ifndef __NEAT_ORGANISM_HPP__
#define __NEAT_ORGANISM_HPP__

#include "genome.hpp"
#include "network.hpp"

#include <algorithm>
#include <random>

class Innovation;
#include "innovation.hpp"

class Organism {
private:
  static Innovation* innovation;

  // Mutation
  void _mutate_add_connection();
  void _mutate_add_node();
  void _mutate_randomized_weight(Connection* connection);
  void _mutate_adjust_weight(Connection* connection);
  void _mutate_toggle_link(Connection* connection);

  void _add_node(Gene* node);
  void _add_connection(Connection* connection);

public:
  Genome* genotype;
  Network* phenotype;
  decimal fitness = 0.0;

  Organism();
  Organism(Genome* genome);
  Organism(Organism* org);
  ~Organism();

  static void set_innovation(Innovation* Innovation);

  std::vector<decimal> forward(const std::vector<decimal>& input);
  decimal calculate_distance(Organism* org);

  Organism* breed(Organism* other);
  void mutate();
};

#endif