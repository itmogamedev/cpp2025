#include "Vec3.h"

#include <iostream>

int main() {
  Vec3 a(1, 2, 3), b(4, 5, 6);
  std::cout << a << std::endl;
  a = a + b;
  std::cout << a << std::endl;
  std::cout << a.length() << std::endl;
}
