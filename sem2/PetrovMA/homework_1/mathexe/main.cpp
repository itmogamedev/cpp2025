#include <iostream>

#include "libs/mathlib.h"

int main() {
  mathlib::Vec3 v1 = {1, 2, 3};
  mathlib::Vec3 v2 = {3, 2, 1};
  std::cout << v1 << " " << v2 << std::endl;
  std::cout << v1 * v2 << std::endl;
  std::cout << v1 + v2 << std::endl;
  std::cout << v1 - v2 << std::endl;
  std::cout << cross(v1, v2) << std::endl;
  std::cout << v1.length() << std::endl;
  std::cout << v1.normalize() << std::endl;
  std::cout << v1.normalize().length() << std::endl;
  return 0;
}