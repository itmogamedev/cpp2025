#include <iostream>

#include "vec3.h"

int main() {
  mathlib::Vec3 v1(1, 2, 3);
  mathlib::Vec3 v2(4, 5, 6);

  std::cout << "v1 = " << v1 << "\nv2 = " << v2 << std::endl;
  std::cout << "v1 + v2 = " << (v1 + v2) << std::endl;
  std::cout << "Dot: " << v1.dot(v2) << "\nCross: " << v1.cross(v2)
            << std::endl;
  std::cout << "Length: " << v1.length() << "\nNormalized: " << v1.normalize()
            << std::endl;

  return 0;
}
