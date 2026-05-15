#include "Vec3.h"

#include <iostream>

void demo() {
  double x, y, z;

  std::cout << "A: ";
  std::cin >> x >> y >> z;
  Vec3 a(x, y, z);

  std::cout << "B: ";
  std::cin >> x >> y >> z;
  Vec3 b(x, y, z);

  std::cout << "A + B: " << (a + b) << std::endl;
  std::cout << "A - B: " << (a - b) << std::endl;
  std::cout << "A * B: " << (a * b) << std::endl;
  std::cout << "A x B: " << (a ^ b) << std::endl;

  std::cout << "Length of A: " << a.length() << std::endl;
  std::cout << "Normalized A: " << a.normalized() << std::endl;
}

int main() {
  demo();

  return 0;
}
