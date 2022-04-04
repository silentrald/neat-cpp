#include "parameter.hpp"

int Parameter::input = 0;
int Parameter::output = 0;
int Parameter::population = 0;

// Activation function
genome_activation Parameter::activation = genome_activation::SIGMOID;

// Speciation
decimal Parameter::disjoint_coefficient = 1.0;
decimal Parameter::excess_coefficient = 1.0;
decimal Parameter::weight_diff_coefficient = 0.4;
decimal Parameter::compatibility_threshold = 6.0;
decimal Parameter::survival_threshold = 0.2;
decimal Parameter::no_crossover_probability = 0.001;
decimal Parameter::interspecies_breeding_probability = 0.01;

// Mutation Probability
decimal Parameter::add_node_probability = 0.03;
decimal Parameter::add_connection_probability = 0.05;
decimal Parameter::randomized_weight_probability = 0.1;
decimal Parameter::adjust_weight_probability = 0.8;
decimal Parameter::toggle_link_probability = 0.75;
