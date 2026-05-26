#include "VectorGenerator.h"

#include <algorithm>
#include <chrono>
#include <random>

std::vector<int> VectorGenerator::generate(int size, int minVal, int maxVal) {
  std::vector<int> vec(size);
  unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
  std::mt19937 gen(seed);
  std::uniform_int_distribution<int> dist(minVal, maxVal);
  std::generate(vec.begin(), vec.end(), [&dist, &gen]() { return dist(gen); });
  return vec;
}
