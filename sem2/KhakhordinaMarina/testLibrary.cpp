#include <iostream>
#include "MathLibrary.h"

void testLibrary() {
  Vec a(1.0, 2.0, 3.0);
  Vec b(4.0, 5.0, 6.0);

  std::cout << "Vector A: " << a << std::endl;
  std::cout << "Vector B: " << b << std::endl;

  Vec s = a + b;
  std::cout << "A + B = " << s << std::endl;

  Vec d = a - b;
  std::cout << "A - B = " << d << std::endl;

  Vec m = a * 10.0;
  std::cout << "A * 10 = " << m << std::endl;

  float sk = a * b;
  std::cout << "A * B (scalar) = " << sk << std::endl;

  Vec cr = a.cross(b);
  std::cout << "A vec proiz B = " << cr << std::endl;

  float len = a.length();
  std::cout << "Length A: " << len << std::endl;

  Vec n = a.normalize();
  std::cout << "Normalize A: " << n << std::endl;
}