#ifndef __NEAT_FUNCTION_HPP__
#define __NEAT_FUNCTION_HPP__

#include "def.hpp"
#include <execinfo.h>
#include <math.h>

namespace Function {
int max(int i1, int i2);
int min(int i1, int i2);
decimal maxf(decimal d1, decimal d2);
decimal minf(decimal d1, decimal d2);
decimal clampf(decimal val, decimal min, decimal max);
int randi(int n);
// long long permutation(int n, int r);
// long long combination(int n, int r);
// long long summation(int n);

decimal randf();

decimal sigmoid_activation(decimal d);
decimal tanh_activation(decimal d);
} // namespace Function

#endif