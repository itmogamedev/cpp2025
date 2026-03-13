#include <iostream>
#include "MathLibrary.h"

void test() {
  double x, y, z, scalar;
  std::cout << "Input vector a: ";
  std::cin >> x >> y >> z;
  Vec3 a(x, y, z);
  std::cout << "Input vector b: ";
  std::cin >> x >> y >> z;
  Vec3 b(x, y, z);
  std::cout << "Input scalar: ";
  std::cin >> scalar;
  std::cout << "Vector sum: " << a + b << '\n';
  std::cout << "Vector difference: " << a - b << '\n';
  std::cout << "Multiplication of a vector a" << a
    << " by a scalar: " << a * scalar << '\n';
  std::cout << "Dot product: " << a * b << '\n';
  std::cout << "Vector product: " << a.crossProd(b) << '\n';
  std::cout << "The lenght of a vector a" << a
    << ": " << a.lenVec() << '\n';
  std::cout << "Normalization of a vector a" << a
    << ": " << a.normVec() << '\n';
  std::cout << "The lenght of vector b" << b
    << ": " << b.lenVec() << '\n';
  std::cout << "Normalization of a vector b" << b
    << ": " << b.normVec() << '\n';
}

int main() {
  test();
  return 0;
}