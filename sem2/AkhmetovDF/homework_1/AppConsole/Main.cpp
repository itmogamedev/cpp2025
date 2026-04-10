#include <iostream>

#include "Vec3.h"

int main() {
  Vec3 vector_a(1.0, 2.0, 3.0);
  Vec3 vector_b(4.0, 5.0, 6.0);

  std::cout << "a = " << vector_a << std::endl;
  std::cout << "b = " << vector_b << std::endl;

  std::cout << "a + b = " << (vector_a + vector_b) << std::endl;
  std::cout << "a - b = " << (vector_a - vector_b) << std::endl;
  std::cout << "a * 2.5 = " << (vector_a * 2.5) << std::endl;
  std::cout << "3.0 * b = " << (3.0 * vector_b) << std::endl;
  std::cout << "dot(a, b) = " << dot(vector_a, vector_b) << std::endl;
  std::cout << "cross(a, b) = " << cross(vector_a, vector_b) << std::endl;
  std::cout << "|a| = " << vector_a.length() << std::endl;

  Vec3 normalized = vector_a;
  normalized.normalize();
  std::cout << "normalized a = " << normalized
            << ", length = " << normalized.length() << std::endl;

  return 0;
}
