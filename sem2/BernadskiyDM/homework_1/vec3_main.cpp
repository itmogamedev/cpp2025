#include <iostream>
#include "Vec3.h"

void demonstrateVec3Operations() {
  Vec3 a(1.0, 2.0, 3.0);
  Vec3 b(4.0, 5.0, 6.0);

  Vec3 sum = a + b;
  Vec3 diff = a - b;
  Vec3 scaled1 = a * 2.0;
  Vec3 scaled2 = 0.5 * b;
  double dotAB = Vec3::dot(a, b);
  Vec3 crossAB = Vec3::cross(a, b);
  double lenA = a.length();
  Vec3 normA = a.normalized();

  std::cout << "a = " << a << std::endl;
  std::cout << "b = " << b << std::endl;
  std::cout << "a + b = " << sum << std::endl;
  std::cout << "a - b = " << diff << std::endl;
  std::cout << "a * 2 = " << scaled1 << std::endl;
  std::cout << "0.5 * b = " << scaled2 << std::endl;
  std::cout << "dot(a, b) = " << dotAB << std::endl;
  std::cout << "cross(a, b) = " << crossAB << std::endl;
  std::cout << "length(a) = " << lenA << std::endl;
  std::cout << "normalized(a) = " << normA << std::endl;
}

int main() {
  demonstrateVec3Operations();
  return 0;
}