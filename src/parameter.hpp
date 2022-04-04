#ifndef __NEAT_PARAMETER_HPP__
#define __NEAT_PARAMETER_HPP__

#include "def.hpp"

enum genome_activation { SIGMOID, TANH };

class Parameter {
public:
  static int input;
  static int output;
  static int population;

  // Activation function
  static genome_activation activation;

  // Speciation
  static decimal disjoint_coefficient;
  static decimal excess_coefficient;
  static decimal weight_diff_coefficient;
  static decimal compatibility_threshold;
  static decimal survival_threshold;
  static decimal no_crossover_probability;
  static decimal interspecies_breeding_probability;

  // Mutation Probability
  static decimal add_node_probability;
  static decimal add_connection_probability;
  static decimal randomized_weight_probability;
  static decimal adjust_weight_probability;
  static decimal toggle_link_probability;
};

#endif