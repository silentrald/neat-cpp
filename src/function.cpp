#include "function.hpp"

int Function::max(int i1, int i2) {
  return i1 > i2 ? i1 : i2;
}

int Function::min(int i1, int i2) {
  return i1 < i2 ? i1 : i2;
}

decimal Function::maxf(decimal d1, decimal d2) {
  return d1 > d2 ? d1 : d2;
}

decimal Function::minf(decimal d1, decimal d2) {
  return d1 < d2 ? d1 : d2;
}

decimal Function::clampf(decimal val, decimal min, decimal max) {
  return Function::maxf(min, Function::minf(max, val));
}

int Function::randi(int n) {
  return rand() % n;
}

// long long Function::permutation(long long n, long long r) {
//   long long count = 1LL;
//   for (long long i = n; i > n - r; i--)
//     count *= i;
//   return count;
// }

// long long Function::combination(long long n, long long r) {
//   long long count = 1LL;
//   long long nr = n - r;

//   // To avoid overflowing
//   for (long long i = n; i > n - r + 1; i--) {
//     count *= i;
//     while (count % r == 0)
//       count /= r;
//     while (count % nr == 0)
//       count /= nr;
//   }
//   return count;
// }

// long long Function::summation(long long n) {
//   return n & 1 ? (n + 1) / 2L * (n + 2) : (n + 2) / 2L * (n + 1);
// }

decimal Function::randf() {
  return (decimal)rand() / (decimal)RAND_MAX;
}

decimal Function::sigmoid_activation(decimal d) {
  return 1 / (1 + exp(-d));
}

decimal Function::tanh_activation(decimal d) {
  return tanh(d);
}