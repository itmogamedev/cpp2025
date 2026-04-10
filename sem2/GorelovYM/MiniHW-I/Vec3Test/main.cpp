#include <vec3.h>

#include <iostream>

// тестики
int main() {
  Vec3 a(1, 2, 3);
  Vec3 b(3, 2, 1);

  std::cout << "a:\t" << a << std::endl;
  std::cout << "b:\t" << b << std::endl;
  std::cout << "a + b:\t" << a + b << std::endl;
  std::cout << "a - b:\t" << a - b << std::endl;
  std::cout << "2 * a:\t" << 2 * a << std::endl;
  std::cout << "b * 3:\t" << b * 3 << std::endl;
  std::cout << "a * b:\t" << a * b << std::endl;
  std::cout << "a x b:\t" << a.vector(b) << std::endl;
  std::cout << "|a|:\t" << a.length() << std::endl;
  std::cout << "|b|:\t" << b.length() << std::endl;
  std::cout << "norm a:\t" << a.normalized() << std::endl;
  std::cout << "norm b:\t" << b.normalized() << std::endl;
}
