#include "random_generator.h"

#include <algorithm>
#include <random>

std::vector<int> generate_random_vector() {
  std::vector<int> vec(20);
  std::mt19937 gen(std::random_device{}());
  std::uniform_int_distribution<int> dist(-50, 100);

  std::generate(vec.begin(), vec.end(), [&gen, &dist]() { return dist(gen); });

  return vec;
}
