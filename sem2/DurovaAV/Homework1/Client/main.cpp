#include <iostream>

#include "vec3.h"

int main() {
  double x1, y1, z1;
  double x2, y2, z2;

  std::cout << "Enter first vector (x y z): " << std::endl;
  std::cin >> x1 >> y1 >> z1;
  std::cout << "Enter second vector (x y z): " << std::endl;
  std::cin >> x2 >> y2 >> z2;

  Vec3 vec1(x1, y1, z1);
  Vec3 vec2(x2, y2, z2);

  std::cout << "\nVector 1: " << vec1 << std::endl;
  std::cout << "Vector 2: " << vec2 << std::endl;

  std::cout << "\nvec1 + vec2 = " << (vec1 + vec2) << std::endl;
  std::cout << "vec1 - vec2 = " << (vec1 - vec2) << std::endl;

  double scalar;
  std::cout << "\nEnter scalar value: " << std::endl;
  std::cin >> scalar;

  std::cout << "vec1 * scalar = " << (vec1 * scalar) << std::endl;
  std::cout << "scalar * vec1 = " << (scalar * vec1) << std::endl;

  std::cout << "\nDot product (vec1, vec2) = " << vec1.dot(vec2) << std::endl;
  std::cout << "Cross product vec1 x vec2 = " << vec1.cross(vec2) << std::endl;

  std::cout << "\nLength of vec1: " << vec1.length() << std::endl;
  std::cout << "Length of vec2: " << vec2.length() << std::endl;

  std::cout << "\nNormalized vec1: " << vec1.normalized() << std::endl;
  std::cout << "Normalized vec2: " << vec2.normalized() << std::endl;

  return 0;
}
