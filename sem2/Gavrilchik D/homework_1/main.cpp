#include <iostream>

#include "vec3.h"

int main() {
  Vec3 a(1.0, 2.0, 3.0);
  Vec3 b(4.0, 5.0, 6.0);

  Vec3 sum = a + b;
  Vec3 diff = a - b;
  Vec3 scaled = a * 2.0;
  double scalar_product = dot(a, b);
  Vec3 vector_product = cross(a, b);

  std::cout << "a = " << a << '\n';
  std::cout << "b = " << b << '\n';
  std::cout << "a + b = " << sum << '\n';
  std::cout << "a - b = " << diff << '\n';
  std::cout << "a * 2 = " << scaled << '\n';
  std::cout << "dot(a, b) = " << scalar_product << '\n';
  std::cout << "cross(a, b) = " << vector_product << '\n';
  std::cout << "length(a) = " << a.length() << '\n';
  std::cout << "normalized(a) = " << a.normalized() << '\n';

  return 0;
}