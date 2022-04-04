#include "network.hpp"

Network::Network() {}

Network::Network(Genome* genome) {
  this->_create_graph(genome);
}

Network::~Network() {}

decimal Network::_activation_function(decimal d) {
  switch (Parameter::activation) {
  case SIGMOID:
    return Function::sigmoid_activation(d);
  case TANH:
    return Function::tanh_activation(d);
  default:
    return d;
  }
}

decimal Network::_node_forward(int innov) {
  if (this->node_values.find(innov) != this->node_values.end()) {
    return this->node_values[innov];
  }

  decimal val = (decimal)0.0;

  auto end_it = this->graph.upper_bound(innov);
  Connection* connection = NULL;
  for (auto it = this->graph.lower_bound(innov); it != end_it; it++) {
    connection = it->second;
    if (connection->enabled)
      val += connection->weight * this->_node_forward(connection->in->innov);
  }

  val = this->_activation_function(val);
  this->node_values[innov] = val;
  return val;
}

// Input should be normalized
std::vector<decimal> Network::forward(const std::vector<decimal>& input) {
  std::vector<decimal> output;

  if (Parameter::input != input.size()) {
    // TODO: Throw error here
    return output;
  }

  // Input Nodes
  for (int i = 0; i < Parameter::input; i++) {
    this->node_values[i] = input[i];
  }
  // Bias Node
  this->node_values[Parameter::input + Parameter::output] = 1.0;

  // Output Nodes
  for (int i = Parameter::input; i < Parameter::input + Parameter::output; i++) {
    output.push_back(this->_node_forward(i));
  }
  this->node_values.clear();

  return output;
}

void Network::_create_graph(Genome* genome) {
  // Check if cyclic
  for (auto it = genome->connection_genes.begin(); it != genome->connection_genes.end(); it++) {
    this->add_connection(it->second);
  }

  if (this->is_cyclic()) {
    this->_remove_cycle();
  }
}

// Did not get called I guess
void Network::rebuild_graph(Genome* genome) {
  this->graph.clear();
  this->_create_graph(genome);
}

// Cycle Detection
bool Network::_is_cyclic_recursion(int vertex, std::unordered_set<int>& visited, std::unordered_set<int>& stack) {
  // Vertex is visited
  if (visited.find(vertex) != visited.end())
    return false;

  visited.insert(vertex);
  stack.insert(vertex);

  Connection* connection = NULL;
  auto end_it = this->graph.upper_bound(vertex);
  int innov;
  for (auto it = this->graph.lower_bound(vertex); it != end_it; it++) {
    connection = it->second;
    innov = connection->in->innov;
    if (!connection->enabled)
      continue;

    if (_is_cyclic_recursion(innov, visited, stack)) {
      return true;
    } else if (stack.find(innov) != stack.end()) {
      return true;
    }
  }

  stack.erase(vertex);

  return false;
}

bool Network::is_cyclic_with_connection(Connection* connection) {
  // Cycle check using dfs
  std::unordered_set<int> visited;
  std::unordered_set<int> stack_set;

  visited.insert(connection->out->innov);
  stack_set.insert(connection->out->innov);

  return this->_is_cyclic_recursion(connection->in->innov, visited, stack_set);
}

bool Network::is_cyclic() {
  std::unordered_set<int> visited;
  std::unordered_set<int> stack_set;
  for (int i = Parameter::input; i < Parameter::input + Parameter::output; i++) {
    if (this->_is_cyclic_recursion(i, visited, stack_set))
      return true;
  }
  return false;
}

void Network::_remove_cycle_recursion(int vertex, std::unordered_set<int>& visited, std::unordered_set<int>& stack) {
  // Vertex visited
  if (visited.find(vertex) != visited.end())
    return;

  visited.insert(vertex);
  stack.insert(vertex);

  Connection* connection = NULL;
  auto end_it = this->graph.upper_bound(vertex);
  int innov;
  for (auto it = this->graph.lower_bound(vertex); it != end_it; it++) {
    connection = it->second;
    innov = connection->in->innov;
    if (!connection->enabled)
      continue;

    this->_remove_cycle_recursion(innov, visited, stack);
    if (stack.find(innov) != stack.end())
      connection->enabled = false;

    stack.erase(vertex);
  }
}

// TODO: If too slow, optimize this
void Network::_remove_cycle() {
  std::unordered_set<int> visited;
  std::unordered_set<int> stack_set;
  while (this->is_cyclic()) {
    visited.clear();
    stack_set.clear();
    for (int i = Parameter::input; i < Parameter::input + Parameter::output; i++) {
      this->_remove_cycle_recursion(i, visited, stack_set);
    }
  }
}
// Cycle Detection

void Network::add_connection(Connection* connection) {
  this->graph.emplace(connection->out->innov, connection);
}

void Network::remove_connection(Connection* connection) {
  // TODO: not implemented
}