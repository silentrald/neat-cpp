#include <iostream>

#include "../src/neat.hpp"

int main() {
  srand(time(NULL));
  // unsigned int t = time(NULL);
  // srand(t);
  // std::cout << t << "\n";
  // srand(1648920599);
  Neat neat(2, 1, 10);

  // Print all descriptions of all organisms
  int i = 0;
  Organism* org;
  // for (auto it = neat.organisms.begin(); it != neat.organisms.end(); it++) {
  //   org = *it;
  //   std::cout << org->genotype->to_string() << "\n";
  // }

  // XOR test
  // 0 xor 0 = 0
  // 0 xor 1 = 1
  // 1 xor 0 = 1
  // 1 xor 1 = 0
  std::vector<decimal> input = {0.0, 0.0};
  decimal output = 0.0;
  for (int gen = 0; gen < 100; gen++) {
    std::cout << "Generation " << gen + 1 << "\n";

    for (int i1 = 0; i1 < 2; i1++) {
      input[0] = (decimal)i1;
      for (int i2 = 0; i2 < 2; i2++) {
        input[1] = (decimal)i2;

        std::cout << i1 << " ^ " << i2 << " = " << (i1 ^ i2) << "; ";

        i = 0;
        for (auto it = neat.organisms.begin(); it != neat.organisms.end(); it++) {
          output = (*it)->forward(input)[0];
          printf("%d ", output > 0.5);
          output = (i1 ^ i2) - output;
          output = 1.0 - (output > 0 ? output : -output);
          (*it)->fitness += output;
        }
        printf("\n");
      }
    }

    neat.create_next_generation();
  }

  // for (auto it = neat.organisms.begin(); it != neat.organisms.end(); it++) {
  //   org = *it;
  //   std::cout << org->genotype->to_string() << "\n";
  // }

  // std::cout << neat.innovation.to_string();

  std::cout << "END\n";

  return 0;
}