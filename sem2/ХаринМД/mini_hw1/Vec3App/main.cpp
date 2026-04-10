#include <iostream>
#include "vec3.h"

int main() {
  Vec3 a(1, 2, 3), b(4, 5, 6);
  std::cout << "a = " << a << "\n";
  std::cout << "b = " << b << "\n";
  std::cout << "a + b = " << a + b << "\n";
  std::cout << "dot(a,b) = " << Vec3::dot(a, b) << "\n";
  std::cout << "cross(a,b) = " << Vec3::cross(a, b) << "\n";
}