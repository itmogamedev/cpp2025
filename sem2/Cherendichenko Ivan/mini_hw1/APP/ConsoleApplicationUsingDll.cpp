#include <iostream>

#include "MathVectorLibrary.h"

int main() {
  Vec3 v1(1.0, 2.0, 3.0);
  Vec3 v2(4.0, 5.0, 6.0);

  std::cout << "v1: " << v1 << std::endl;
  std::cout << "v2: " << v2 << std::endl;

  Vec3 sum = v1 + v2;
  std::cout << "v1 + v2: " << sum << std::endl;

  Vec3 diff = v1 - v2;
  std::cout << "v1 - v2: " << diff << std::endl;

  Vec3 scaled = v1 * 2.0;
  std::cout << "v1 * 2: " << scaled << std::endl;

  double dot = dotProduct(v1, v2);
  std::cout << "Dot product (v1, v2): " << dot << std::endl;

  Vec3 cross = crossProduct(v1, v2);
  std::cout << "Cross product (v1, v2): " << cross << std::endl;

  std::cout << "Length of v1: " << v1.length() << std::endl;

  Vec3 normalized_v1 = v1;
  normalized_v1.normalize();
  std::cout << "Normalized v1: " << normalized_v1 << std::endl;

  return 0;
}
