#include <iostream>

#include "Vec3.h"

int main() {
  Vec3 v1 = {5, 10, 7};
  Vec3 v2 = {3, 4, 9};

  std::cout << "vector 1: " << v1 << std::endl;
  std::cout << "vector 2: " << v2 << std::endl;
  std::cout << "1. summ v1 + v2 = " << v1 + v2 << std::endl;
  std::cout << "2. * v1 by a scalar = " << v1 * 5 << std::endl;
  std::cout << "3. dot product = " << dotProduct(v1, v2) << std::endl;
  std::cout << "4. vector product = " << vectorProduct(v1, v2) << std::endl;
  std::cout << "5. vector 1 len = " << vectorLength(v1) << std::endl;
  std::cout << "6. vector 2 normalize = " << vectorNormalize(v2) << std::endl;
  return 0;
}
