#ifndef __NEAT_HPP__
#define __NEAT_HPP__

#include "innovation.hpp"
#include "organism.hpp"
#include "parameter.hpp"
#include "species.hpp"

#include <vector>

class Neat {
private:
  void _speciation();
  void _extinction();
  void _reproduction();
  void _cleanup();

public:
  Innovation innovation;
  std::vector<Organism*> organisms;
  std::vector<Species*> species;

  Neat(int input, int output, int population = 100);
  ~Neat();

  void init(int input, int output, int population = 100);
  void create_next_generation();
};

#endif