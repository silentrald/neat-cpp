#ifndef __NEAT_NODE_HPP__
#define __NEAT_NODE_HPP__

#include <string>

enum gene_type : int { INPUT, OUTPUT, HIDDEN, BIAS };

class Gene {
public:
  int innov;
  gene_type type;

  Gene();
  Gene(int innov, gene_type type = gene_type::HIDDEN);

  // Might not be used since all nodes will use the same reference
  bool operator==(const Gene& gene);

  std::string to_string();
};

#endif