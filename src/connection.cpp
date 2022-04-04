#include "connection.hpp"

Connection::Connection() {}

Connection::Connection(Gene* in, Gene* out, decimal weight, bool enabled, int innov) {
  this->in = in;
  this->out = out;
  this->weight = weight;
  this->enabled = enabled;
  this->innov = innov;
}

Connection::Connection(Connection* connection) {
  this->in = connection->in;
  this->out = connection->out;
  this->weight = connection->weight;
  this->enabled = connection->enabled;
  this->innov = connection->innov;

  // For Global Innovation
  this->in_con = connection->in_con;
  this->out_con = connection->out_con;
}

bool Connection::operator==(const Connection& con) {
  return this->innov == con.innov;
}

// TODO: Look at the format in other literatures
std::string Connection::to_string() {
  return "Connection " + std::to_string(this->innov) + " " + std::to_string(this->in->innov) + " -> " +
         std::to_string(this->out->innov) + " " + std::to_string(this->weight) + " " +
         (this->enabled ? "ENABLED" : "DISABLED");
}
