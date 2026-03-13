#include <iostream>

#include "MathLibrary.h"

int main() {
  Vec3 a(1, 2, 3);
  Vec3 b(4, 5, 6);

  std::cout << "a = " << a << std::endl;
  std::cout << "b = " << b << std::endl;
  std::cout << "-------------------" << std::endl;

  // Addition
  std::cout << "a + b = " << a + b << std::endl;

  // Subtraction
  std::cout << "a - b = " << a - b << std::endl;

  // Scalar multiplication
  std::cout << "a * 2.5 = " << a * 2.5 << std::endl;
  std::cout << "3 * a = " << 3.0 * a << std::endl;

  // Dot product
  std::cout << "a dot b = " << a.dot(b) << std::endl;

  // Cross product
  std::cout << "a cross b = " << a.cross(b) << std::endl;

  // Vector length
  std::cout << "|a| = " << a.length() << std::endl;
  std::cout << "|b| = " << b.length() << std::endl;

  // Normalization
  std::cout << "norm(a) = " << a.normalize() << std::endl;
  std::cout << "norm(b) = " << b.normalize() << std::endl;

  // Checking length after normalization
  std::cout << "|norm(a)| = " << a.normalize().length() << std::endl;

  return 0;
}
