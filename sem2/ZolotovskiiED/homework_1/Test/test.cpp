#include <iostream>

#include "vector_lib.h"

int main() {
  Vec3 v1(1.0f, 2.0f, 3.0f);
  Vec3 v2(4.0f, 5.0f, 6.0f);

  std::cout << "Vector 1: " << v1 << std::endl;
  std::cout << "Vector 2: " << v2 << std::endl;

  // Сложение
  std::cout << "v1 + v2 = " << (v1 + v2) << std::endl;

  // Вычитание
  std::cout << "v1 - v2 = " << (v1 - v2) << std::endl;

  // Умножение вектора на скаляр
  std::cout << "v1 * 3 = " << (v1 * 3.0f) << std::endl;

  // Умножение скаляра на вектор
  std::cout << "v1 * 3 = " << (v1 * 3.0f) << std::endl;

  // Скалярное произведение
  std::cout << "v1 * v2 = " << (v1 * v2) << std::endl;

  // Векторное произведение
  std::cout << "Cross = " << (v1 ^ v2) << std::endl;

  // Длина
  std::cout << "Length v1 = " << v1.length() << std::endl;

  // Нормализация
  std::cout << "Normalized v1 = " << v1.normalize() << std::endl;

  return 0;
}
