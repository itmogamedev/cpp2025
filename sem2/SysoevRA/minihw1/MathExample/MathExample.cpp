#include <iostream>

#include "MathLibrary.h"

int math() {
  Vec3 a(1, 2, 3);
  Vec3 b(4, 5, 6);

  std::cout << "a = " << a << std::endl;
  std::cout << "b = " << b << std::endl;

  Vec3 sum = a + b;
  std::cout << "a + b = " << sum << std::endl;

  Vec3 diff = a - b;
  std::cout << "a - b = " << diff << std::endl;

  Vec3 mul = a * 2.5;
  std::cout << "a * 2.5 = " << mul << std::endl;

  double dotProd = scalarProduct(a, b);
  std::cout << "scalarProduct(a, b) = " << dotProd << std::endl;

  Vec3 crossProd = vectorProduct(a, b);
  std::cout << "vectorProduct(a, b) = " << crossProd << std::endl;

  double lenght = vectorLength(a);
  std::cout << "|a| = " << lenght << std::endl;

  Vec3 normA = normalizeVector(a);
  std::cout << "normalize(a) = " << normA << std::endl;
  std::cout << "length(normalize(a)) = " << vectorLength(normA) << std::endl;

  return 0;
}

int main() {
  math();
  return 0;
}
