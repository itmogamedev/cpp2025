#include <iostream>

#include "vec3.h"

int main() {
  Vec3 a(1.0, 2.0, 3.0);
  Vec3 b(4.0, 5.0, 6.0);

  std::cout << "a = " << a << "\nb = " << b << std::endl;
  std::cout << "a + b = " << (a + b) << std::endl;
  std::cout << "a - b = " << (a - b) << std::endl;
  std::cout << "2 * a = " << (2.0 * a) << std::endl;
  std::cout << "dot(a, b) = " << dot(a, b) << std::endl;
  std::cout << "cross(a, b) = " << cross(a, b) << std::endl;
  std::cout << "|a| = " << a.length() << std::endl;

  Vec3 norm = a;
  norm.normalize();
  std::cout << "normalized a = " << norm << std::endl;

  return 0;
}
