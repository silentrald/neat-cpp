#ifndef __NEAT_NETWORK_HPP__
#define __NEAT_NETWORK_HPP__

#include "connection.hpp"
#include "def.hpp"

#include <iostream>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Genome;
#include "genome.hpp"

// TODO: Add a way to display this on to a screen or console
// Might create a node class
class Network {
private:
  std::multimap<int, Connection*> graph;
  std::unordered_map<int, decimal> node_values;

  void _create_graph(Genome* genome);
  decimal _activation_function(decimal d);
  decimal _node_forward(int innov);

  bool _is_cyclic_recursion(int vertex, std::unordered_set<int>& visited, std::unordered_set<int>& stack);
  void _remove_cycle_recursion(int vertex, std::unordered_set<int>& visited, std::unordered_set<int>& stack);
  void _remove_cycle();

public:
  Network();
  Network(Genome* genome);
  ~Network();

  std::vector<decimal> forward(const std::vector<decimal>& input);
  void rebuild_graph(Genome* genome);

  // Check if connection is valid
  bool is_cyclic_with_connection(Connection* connection);
  bool is_cyclic();
  void add_connection(Connection* connection);
  void remove_connection(Connection* connection);
};

#endif