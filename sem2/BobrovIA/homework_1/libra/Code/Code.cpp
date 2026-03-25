#include <iostream>

#include "Libra.h"

int main() {
  Vec3 v1(1, 2, 3);
  Vec3 v2(4, 5, 6);
  std::cout << "v1: " << v1 << std::endl;
  std::cout << "v2: " << v2 << std::endl;

  Vec3 sum = v1 + v2;
  Vec3 dif = v1 - v2;
  std::cout << "Sum (+): " << sum << std::endl;
  std::cout << "Dif (-): " << dif << std::endl;

  float scalar = 2.0f;
  Vec3 scaled = v1 * scalar;
  std::cout << "Scaled (v1 * 2): " << scaled << std::endl;

  float dotResult = v1 * v2;
  std::cout << "Dot product (*): " << dotResult << std::endl;

  Vec3 crossResult = v1.cross(v2);
  std::cout << "Cross product: " << crossResult << std::endl;

  float v1Length = v1.length();
  Vec3 v1Normalized = v1.normalize();
  std::cout << "V1 Length: " << v1Length << std::endl;
  std::cout << "V1 Normalized: " << v1Normalized << std::endl;

  return 0;
}
