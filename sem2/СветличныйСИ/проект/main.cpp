#include <iostream>

#include "library.h"

int main() {
  Vec3 a = Vec3(1, 2, 3);
  Vec3 b = Vec3(4, 5, 6);

  std::cout << a+b << std::endl;
  std::cout << a-b << std::endl;
  std::cout << a*b << std::endl;
  std::cout << a*2 << std::endl;
  std::cout << (a^b) << std::endl;
  std::cout << a.length() << std::endl;
  std::cout << a.normalize() << std::endl;
}

