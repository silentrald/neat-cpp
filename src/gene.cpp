#include "gene.hpp"

Gene::Gene() {}

Gene::Gene(int innov, gene_type type) {
  this->innov = innov;
  this->type = type;
}

bool Gene::operator==(const Gene& gene) {
  return this->innov == gene.innov;
}

// TODO: Look at the format in other literatures
std::string Gene::to_string() {
  switch (this->type) {
  case gene_type::INPUT:
    return "Gene " + std::to_string(innov) + " INPUT";
  case gene_type::OUTPUT:
    return "Gene " + std::to_string(innov) + " OUTPUT";
  case gene_type::HIDDEN:
    return "Gene " + std::to_string(innov) + " HIDDEN";
  case gene_type::BIAS:
    return "Gene " + std::to_string(innov) + " BIAS";
  default:
    return "Gene " + std::to_string(innov) + " UNKNOWN";
  }
}
