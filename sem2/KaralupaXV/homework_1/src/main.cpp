#include <iostream>

#include "vec3.h"

int main() {
  Vec3 a(1, 2, 4);
  Vec3 b(2, 6, -2);

  Vec3 c = a.cross(b);
  std::cout << c << "\nlen: " << c.len() << "\n";

  c = c.norm() * 10;

  std::cout << c << "\nlen: " << c.len() << "\n";
}