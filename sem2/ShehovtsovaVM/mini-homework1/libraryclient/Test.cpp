#include <iostream>
#include "Assemble.h"
void TestRun() {
  Vec3 a (1, 1, 1);
  Vec3 b(2, 2, 2);
  Vec3 c = a + b;
  std::cout << c << '\n';
  c = a - b;
  std::cout << c << '\n';
  c = c * 5;
  std::cout << c << '\n';
  std::cout << a.ScalarMultiplication(b) << '\n';
  std::cout << a.VectorMultiplication(b) << '\n';
}