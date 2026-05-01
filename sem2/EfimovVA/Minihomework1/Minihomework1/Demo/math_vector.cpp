#include <iostream>

#include "math_lib.h"

int main() {
  std::cout << "--- Vector Math Library Test ---\n";

  const float SCALAR_VALUE = 2.5f;

  Vec3 vector_a(1.0f, 2.0f, 3.0f);
  Vec3 vector_b(4.0f, 5.0f, 6.0f);

  std::cout << "Vector A: " << vector_a << "\n";
  std::cout << "Vector B: " << vector_b << "\n";

  Vec3 vector_sum = vector_a + vector_b;
  Vec3 vector_sub = vector_b - vector_a;

  std::cout << "A + B: " << vector_sum << "\n";
  std::cout << "B - A: " << vector_sub << "\n";

  Vec3 vector_scaled = vector_a * SCALAR_VALUE;
  std::cout << "A * " << SCALAR_VALUE << ": " << vector_scaled << "\n";

  float dot_result = vector_a.dotProduct(vector_b);
  std::cout << "Dot Product (A . B): " << dot_result << "\n";

  Vec3 cross_result = vector_a.crossProduct(vector_b);
  std::cout << "Cross Product (A x B): " << cross_result << "\n";

  std::cout << "Length of Vector A: " << vector_a.length() << "\n";

  vector_a.normalize();
  std::cout << "Normalized Vector A: " << vector_a << "\n";
  std::cout << "Length of Normalized Vector A: " << vector_a.length() << "\n";

  return 0;
}