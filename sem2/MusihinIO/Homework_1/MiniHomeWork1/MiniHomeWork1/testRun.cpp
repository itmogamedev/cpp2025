#include "testRun.h"

#include <iostream>

#include "MathLibrary.h"

void runDemo() {
  Vec3 a(1.0, 2.0, 3.0);
  Vec3 b(4.0, 5.0, 6.0);

  std::cout << "a = " << a << "\n";
  std::cout << "b = " << b << "\n\n";

  std::cout << "a + b = " << (a + b) << "\n";
  std::cout << "a - b = " << (a - b) << "\n\n";

  std::cout << "a * 3 = " << (a * 3.0) << "\n";
  std::cout << "2.5 * b = " << (2.5 * b) << "\n\n";

  std::cout << "a.add(b) = " << a.add(b) << "\n";
  std::cout << "a.subtract(b) = " << a.subtract(b) << "\n";
  std::cout << "a.multiply(4) = " << a.multiply(4.0) << "\n\n";

  std::cout << "a.dot(b) = " << a.dot(b) << "\n";

  std::cout << "a.cross(b) = " << a.cross(b) << "\n\n";

  std::cout << "a.length() = " << a.length() << "\n";
  std::cout << "a.normalize() = " << a.normalize() << "\n";
  std::cout << "|a.normalize()| = " << a.normalize().length() << "\n";
}
