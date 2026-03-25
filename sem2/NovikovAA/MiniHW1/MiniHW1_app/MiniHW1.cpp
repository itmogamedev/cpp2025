#include <iostream>

#include "vec3.h"

int main() {
  Vec3 a(1, 2, 3);
  Vec3 b(4, 5, 6);
  Vec3 c = a + b;
  std::cout << "a + b = " << c << std::endl;
  std::cout << "dot = " << a.dot(b) << std::endl;
  std::cout << "cross = " << a.cross(b) << std::endl;
  std::cout << "|a| = " << a.length() << "\nnormalize(a) = " << a.normalize()
            << std::endl;
}
