#pragma comment(lib, "MathLibrary.lib")
#include <iostream>

#include "Vec3.h"

int main() {
  Vec3 v1(1, 2, 2);
  Vec3 v2(4, 5, 6);

  std::cout << "V1: " << v1 << " | Length: " << v1.length() << std::endl;
  std::cout << "V1 Normalized: " << v1.normalize() << std::endl;
  std::cout << "V1 + V2 = " << (v1 + v2) << std::endl;
  std::cout << "Scalar product (V1 * V2): " << (v1 * v2) << std::endl;
  std::cout << "Cross product: " << v1.cross(v2) << std::endl;

  return 0;
}
