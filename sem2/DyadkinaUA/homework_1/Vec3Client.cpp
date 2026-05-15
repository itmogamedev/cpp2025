#include <iostream>

#include "vec3.h"

int main() {
  using math::Cross;
  using math::Dot;
  using math::Vec3;

  Vec3 a(1.0, 2.0, 3.0);
  Vec3 b(4.0, 5.0, 6.0);

  Vec3 sum = a + b;
  Vec3 diff = a - b;
  Vec3 scaled = a * 2.0;
  double dot = Dot(a, b);
  Vec3 cross = Cross(a, b);
  double length_a = a.Length();
  Vec3 a_norm = a.Normalized();

  std::cout << "a = " << a << std::endl;
  std::cout << "b = " << b << std::endl;
  std::cout << "a + b = " << sum << std::endl;
  std::cout << "a - b = " << diff << std::endl;
  std::cout << "a * 2 = " << scaled << std::endl;
  std::cout << "dot(a, b) = " << dot << std::endl;
  std::cout << "cross(a, b) = " << cross << std::endl;
  std::cout << "|a| = " << length_a << std::endl;
  std::cout << "normalized(a) = " << a_norm << std::endl;

  return 0;
}
