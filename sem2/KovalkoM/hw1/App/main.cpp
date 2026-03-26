#include <iostream>

#include "Vec3.h"

int main() {
  using MathLib::cross;
  using MathLib::dot;
  using MathLib::Vec3;

  Vec3 a(1.0f, 2.0f, 3.0f);
  Vec3 b(4.0f, 5.0f, 6.0f);

  std::cout << "a = " << a << '\n';
  std::cout << "b = " << b << '\n';

  Vec3 sum = a + b;
  Vec3 diff = a - b;
  Vec3 scaled = a * 2.0f;
  float d = dot(a, b);
  Vec3 c = cross(a, b);

  std::cout << "a + b = " << sum << '\n';
  std::cout << "a - b = " << diff << '\n';
  std::cout << "a * 2 = " << scaled << '\n';
  std::cout << "dot(a, b) = " << d << '\n';
  std::cout << "cross(a, b) = " << c << '\n';

  std::cout << "length(a) = " << a.length() << '\n';
  Vec3 an = a.normalized();
  std::cout << "normalized(a) = " << an << '\n';
  std::cout << "length(normalized(a)) = " << an.length() << '\n';

  return 0;
}
