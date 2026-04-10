#include <iostream>

#include "math_vector.h"

int main() {
  Vec3 v1(1, 2, 3), v2(4, 5, 6);

  std::cout << "v1 = " << v1 << ", v2 = " << v2 << std::endl;
  std::cout << "v1 + v2 = " << (v1 + v2) << std::endl;
  std::cout << "v1 - v2 = " << (v1 - v2) << std::endl;
  std::cout << "v1 * 2.5 = " << (v1 * 2.5) << std::endl;
  std::cout << "Dot product = " << DotProduct(v1, v2) << std::endl;
  std::cout << "Cross product = " << CrossProduct(v1, v2) << std::endl;
  std::cout << "Length = " << Length(v1) << std::endl;
  std::cout << "Normalized = " << Normalize(v1) << std::endl;

  return 0;
}
