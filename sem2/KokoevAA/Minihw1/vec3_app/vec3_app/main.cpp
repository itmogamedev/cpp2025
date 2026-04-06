#include <iostream>

#include "Vec3.h"

int main() {
  Vec3 a(1.0, 2.0, 3.0);
  Vec3 b(4.0, 5.0, 6.0);

  std::cout << "a = " << a << "\n";
  std::cout << "b = " << b << "\n";
  std::cout << "a + b = " << a + b << "\n";
  std::cout << "a - b = " << a - b << "\n";
  std::cout << "a * 2 = " << a * 2.0 << "\n";
  std::cout << "scalarMult(a, b) = " << a.scalarMultiply(b) << "\n";
  std::cout << "vectMult(a, b) = " << a.vectorMultiply(b) << "\n";
  std::cout << "|a| = " << a.length() << "\n";
  std::cout << "normalize(a) = " << a.normalize() << "\n";

  return 0;
}
