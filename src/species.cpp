#include "species.hpp"

Species::Species(Organism* org) {
  this->candidate = org;

  this->add_organism(org);
}

Species::~Species() {
  delete this->candidate;
}

std::vector<Organism*>::iterator Species::get_organisms_begin() {
  return this->organisms.begin();
}

std::vector<Organism*>::iterator Species::get_organisms_end() {
  return this->organisms.end();
}

int Species::organism_size() {
  return this->organisms.size();
}

void Species::add_organism(Organism* org) {
  this->total_fitness += org->fitness;
  this->max_fitness = Function::maxf(this->max_fitness, org->fitness);
  this->max_fitness_ever = Function::maxf(this->max_fitness_ever, org->fitness);

  // Insertion sort
  for (int i = 0; i < this->organisms.size(); i++) {
    if (org->fitness > this->organisms[0]->fitness) {
      this->organisms.insert(this->organisms.begin() + i, org);
      return;
    }
  }
  this->organisms.push_back(org);
}

void Species::_remove_last_organism() {
  Organism* org = this->organisms.back();
  this->organisms.pop_back();

  this->total_fitness -= org->fitness;

  // Check if the same address
  if (org != this->candidate) {
    delete org;
  }
}

void Species::clear_organism() {
  this->max_fitness = 0.0;
  this->total_fitness = 0.0;
  this->organisms.clear();
}

void Species::kill_organism(decimal survival_rate) {
  int remove = this->organisms.size() - Function::max(1, (int)ceil(this->organisms.size() * survival_rate));

  for (int i = 0; i < remove; i++) {
    this->_remove_last_organism();
  }
}

decimal Species::compare_candidate(Organism* org) {
  return this->candidate->calculate_distance(org);
}

Organism* Species::get_random_organism() {
  return this->organisms[Function::randi(this->organisms.size())];
}

decimal Species::reproduce(std::vector<Organism*>& children, std::vector<Species*>& all_species, decimal total_fitness,
                           decimal fraction) {
  if (this->organisms.size() == 0)
    return fraction;

  // Count how many offsprings to make
  int count = 0;
  decimal frac_part, int_part;
  for (auto it = this->organisms.begin(); it != this->organisms.end(); it++) {
    fraction += (*it)->fitness * Parameter::population / total_fitness;
    if (fraction >= 1.0) {
      frac_part = modf(fraction, &int_part);
      count += (int)int_part;
      fraction = frac_part;
    }
  }

  // Create children
  Organism *child, *parent1, *parent2;
  int r1, r2;
  for (int i = 0; i < count; i++) {
    // Crossover
    if (Function::randf() < Parameter::no_crossover_probability) {
      // No crossover
      child = this->organisms[Function::randi(this->organisms.size())];
    } else if (all_species.size() > 1 && Function::randf() < Parameter::interspecies_breeding_probability) {
      // Interbreeding
      parent1 = this->organisms[Function::randi(this->organisms.size())];
      r1 = Function::randi(all_species.size());
      // Don't select own species
      if (all_species[Function::randi(all_species.size())]->innov == this->innov)
        r1 = (r1 + 1) % all_species.size();
      parent2 = all_species[Function::randi(all_species.size())]->get_random_organism();
      child = parent1->breed(parent2);
    } else {
      // Get two random numbers
      r1 = Function::randi(this->organisms.size());
      r2 = Function::randi(this->organisms.size());
      if (r1 == r2)
        r2 = (r2 + 1) % this->organisms.size();

      parent1 = this->organisms[r1];
      parent2 = this->organisms[r2];
      child = parent1->breed(parent2);
    }

    // Mutations
    child->mutate();

    children.push_back(child);
  }

  return fraction;
}