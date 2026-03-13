#include <iostream>

#include "vec3.h"

int main() {
  setlocale(LC_ALL, "Russian");

  Vec3 a(1.0f, 2.0f, 3.0f);
  Vec3 b(4.0f, 5.0f, 6.0f);

  std::cout << "Вектор A: " << a << std::endl;
  std::cout << "Вектор B: " << b << std::endl;
  std::cout << "Сумма: " << (a + b) << std::endl;
  std::cout << "Скалярное произведение: " << (a * b) << std::endl;
  std::cout << "Длина A: " << a.getLength() << std::endl;

  std::cin.get();

  return 0;
}
