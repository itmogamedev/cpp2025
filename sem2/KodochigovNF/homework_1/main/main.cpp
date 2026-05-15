#include <iostream>

#include "vec3.h"

int main() {
  Vec3 a(1, 2, 3), b(4, 5, 6);
  std::cout << "a + b = " << a + b << ", a - b = " << a - b << "\n";
  std::cout << "dot(a, b) = " << a.dot(b) << ", cross(a, b) = " << a.cross(b)
            << "\n";
  std::cout << "|a| = " << a.length() << ", normalized a = " << a.normalized()
            << "\n";
  std::cout << "a * 2 = " << a * 2 << ", 3 * a = " << 3 * a << "\n";
  return 0;
}
