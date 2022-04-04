#include "innovation.hpp"

// define
std::unordered_map<int, std::pair<int, int>> Innovation::split_connection;
std::unordered_map<std::string, Connection*> Innovation::connection_map;
std::vector<Gene*> Innovation::genes;
std::vector<Connection*> Innovation::connections;

std::string Innovation::_convert_key(int in, int out) {
  return std::to_string(in) + "-" + std::to_string(out);
}

// Gene list functions
Gene* Innovation::create_node(gene_type type) {
  Gene* node = new Gene(Innovation::genes.size(), type);
  // std::cout << "Created Node\n";
  // std::cout << node->to_string() << "\n";
  Innovation::genes.push_back(node);
  return node;
}

Gene* Innovation::get_node(int i) {
  return i < Innovation::genes.size() ? Innovation::genes[i] : NULL;
}

int Innovation::get_nodes_size() {
  return Innovation::genes.size();
}

std::vector<Gene*>::iterator Innovation::get_nodes_begin() {
  return Innovation::genes.begin();
}

std::vector<Gene*>::iterator Innovation::get_nodes_end() {
  return Innovation::genes.end();
}

// Connection list functions
Connection* Innovation::create_connection(Gene* in, Gene* out) {
  Connection* connection = new Connection(in, out, 0.0, true, Innovation::connections.size());
  Innovation::connections.push_back(connection);
  Innovation::connection_map[Innovation::_convert_key(in->innov, out->innov)] = connection;
  return connection;
}

Connection* Innovation::get_connection(int i) {
  return i < Innovation::connections.size() ? Innovation::connections[i] : NULL;
}

Connection* Innovation::get_connection(int in, int out) {
  std::string key = Innovation::_convert_key(in, out);
  return Innovation::connection_map.find(key) != Innovation::connection_map.end() ? Innovation::connection_map[key]
                                                                                  : NULL;
}

Connection* Innovation::get_random_connection() {
  return Innovation::connections[Function::randi(Innovation::connections.size())];
}

int Innovation::get_connections_size() {
  return Innovation::connections.size();
}

std::vector<Connection*>::iterator Innovation::get_connections_begin() {
  return Innovation::connections.begin();
}

std::vector<Connection*>::iterator Innovation::get_connections_end() {
  return Innovation::connections.end();
}
//

Innovation::~Innovation() {
  for (auto it = Innovation::genes.begin(); it != Innovation::genes.end(); it++) {
    delete *it;
  }
  Innovation::genes.clear();

  for (auto it = Innovation::connections.begin(); it != Innovation::connections.end(); it++) {
    delete *it;
  }
  Innovation::connections.clear();
}

std::string Innovation::to_string() {
  std::string str = "Innovation\nGenes:\n";

  for (auto it = Innovation::genes.begin(); it != Innovation::genes.end(); it++) {
    str += (*it)->to_string() + "\n";
  }

  str += "Connections:\n";
  for (auto it = Innovation::connections.begin(); it != Innovation::connections.end(); it++) {
    str += (*it)->to_string() + "\n";
  }

  return str;
}
