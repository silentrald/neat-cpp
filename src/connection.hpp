#ifndef __NEAT_CONNECTION_HPP__
#define __NEAT_CONNECTION_HPP__

#include "def.hpp"
#include "gene.hpp"

#include <string>

class Connection {
public:
  Gene *in, *out;
  decimal weight;
  bool enabled;
  int innov;
  Connection* in_con = NULL;
  Connection* out_con = NULL;

  Connection();
  Connection(Gene* in, Gene* out, decimal weight, bool enabled, int innov);
  Connection(Connection* connection);

  bool operator==(const Connection& con);

  std::string to_string();
};

#endif