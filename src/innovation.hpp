#ifndef __NEAT_INNOVATION_HPP__
#define __NEAT_INNOVATION_HPP__

#include "genome.hpp"

#include <iostream>
#include <unordered_map>
#include <vector>

class Innovation {
private:
  static std::unordered_map<int, std::pair<int, int>> split_connection;
  static std::unordered_map<std::string, Connection*> connection_map;
  static std::vector<Gene*> genes;
  static std::vector<Connection*> connections;

  static std::string _convert_key(int in, int out);

public:
  ~Innovation();

  // Gene List Functions
  Gene* create_node(gene_type type);
  Gene* get_node(int innov);
  int get_nodes_size();
  std::vector<Gene*>::iterator get_nodes_begin();
  std::vector<Gene*>::iterator get_nodes_end();

  // Connection List Functions
  Connection* create_connection(Gene* in, Gene* out);
  Connection* get_connection(int i);
  Connection* get_connection(int in, int out);
  Connection* get_random_connection();
  int get_connections_size();
  std::vector<Connection*>::iterator get_connections_begin();
  std::vector<Connection*>::iterator get_connections_end();

  std::string to_string();
};

#endif