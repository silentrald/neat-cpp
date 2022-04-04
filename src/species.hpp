#ifndef __NEAT_SPECIES_HPP__
#define __NEAT_SPECIES_HPP__

#include "def.hpp"
#include "organism.hpp"

#include <math.h>
#include <vector>

// TODO: Species are evolving too much
class Species {
private:
  // Always sorted
  std::vector<Organism*> organisms;
  Organism* candidate;

  void _remove_last_organism();

protected:
  Organism* get_random_organism();

public:
  int innov;
  decimal total_fitness = 0.0;
  decimal max_fitness = 0.0;
  decimal max_fitness_ever = 0.0;

  Species(Organism* candidate);
  ~Species();

  // Vector functions
  std::vector<Organism*>::iterator get_organisms_begin();
  std::vector<Organism*>::iterator get_organisms_end();
  int organism_size();
  void add_organism(Organism* org);
  void clear_organism();
  void kill_organism(decimal survival_rate);

  decimal compare_candidate(Organism* org);

  // returns a remaining fraction
  decimal reproduce(std::vector<Organism*>& children, std::vector<Species*>& all_species, decimal total_fitness,
                    decimal fraction = 0.0);
};

#endif