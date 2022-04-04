#ifndef __NEAT_GENOME_HPP__
#define __NEAT_GENOME_HPP__

#include "connection.hpp"
#include "def.hpp"
#include "function.hpp"
#include "network.hpp"
#include "parameter.hpp"

#include <set>
#include <unordered_map>
#include <vector>

class Genome {
public:
  std::unordered_map<int, Gene*> node_genes;
  std::unordered_map<int, Connection*> connection_genes;

  Genome();
  Genome(Genome* other);
  ~Genome();

  void add_node(Gene* node);
  void add_connection(Connection* connection);

  decimal calculate_distance(Genome* other);
  Genome* crossover(Genome* other);

  std::string to_string();
};

#endif