#include <iostream>

#include "vector.h"  // подключаем заголовок из DLL

int main() {
  Vec3 a(1, 2, 3);
  Vec3 b(4, 5, 6);

  std::cout << "a = " << a << std::endl;
  std::cout << "b = " << b << std::endl;

  Vec3 plus = a + b;
  std::cout << "a + b = " << plus << std::endl;

  Vec3 minus = a - b;
  std::cout << "a - b = " << minus << std::endl;

  Vec3 scal = a * 2.5f;
  std::cout << "a * 2.5 = " << scal << std::endl;

  float dot = a.scalyarMulti(b);
  std::cout << "a * b = " << dot << std::endl;

  Vec3 cross = a.veсMulti(b);
  std::cout << "a X b = " << cross << std::endl;

  std::cout << "|a| = " << a.lenght() << std::endl;

  Vec3 norm = a.normalezd();
  std::cout << "Normalnoe a = " << norm << std::endl;

  return 0;
}
