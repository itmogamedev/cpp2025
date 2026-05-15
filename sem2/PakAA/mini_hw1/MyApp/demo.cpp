#include "demo.h"

void runDemo() {
  Vec3 a(1.f, 2.f, 3.f);
  Vec3 b(4.f, 5.f, 6.f);

  std::cout << "a = " << a << "\n";
  std::cout << "b = " << b << "\n";
  std::cout << "a + b = " << (a + b) << "\n";
  std::cout << "a - b = " << (a - b) << "\n";
  std::cout << "a * 2 = " << (a * 2.f) << "\n";
  std::cout << "dot(a,b) = " << dot(a, b) << "\n";
  std::cout << "cross(a,b) = " << cross(a, b) << "\n";
  std::cout << "length(a) = " << length(a) << "\n";
  std::cout << "normalize(a) = " << normalize(a) << "\n";
}
