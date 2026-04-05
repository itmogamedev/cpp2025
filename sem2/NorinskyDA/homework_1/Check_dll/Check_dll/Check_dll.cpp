#include <iostream>

#include "MathLibrary.h"

int main() {
  setlocale(0, "");
  std::cout << "=== Тестирование библиотеки Vec3 ===\n\n";

  // Создаем векторы
  Vec3 v1(1.0, 2.0, 3.0);
  Vec3 v2(4.0, 5.0, 6.0);

  std::cout << "v1 = " << v1 << std::endl;
  std::cout << "v2 = " << v2 << std::endl;

  // Сложение
  Vec3 sum = v1 + v2;
  std::cout << "\nСложение v1 + v2 = " << sum << std::endl;

  // Вычитание
  Vec3 diff = v1 - v2;
  std::cout << "Вычитание v1 - v2 = " << diff << std::endl;

  // Умножение на скаляр
  Vec3 mult = v1 * 2.5;
  std::cout << "Умножение v1 * 2.5 = " << mult << std::endl;

  // Деление на скаляр
  Vec3 div = v2 / 2.0;
  std::cout << "Деление v2 / 2.0 = " << div << std::endl;

  // Скалярное произведение
  double dot = dot_product(v1, v2);
  std::cout << "\nСкалярное произведение v1·v2 = " << dot << std::endl;

  // Векторное произведение
  Vec3 cross = cross_product(v1, v2);
  std::cout << "Векторное произведение v1 х v2 = " << cross << std::endl;

  // Длина вектора
  double len = vector_length(v1);
  std::cout << "\nДлина v1 = " << len << std::endl;

  // Нормализация
  Vec3 norm = normalize_vector(v1);
  std::cout << "Нормализованный v1 = " << norm << std::endl;
  std::cout << "Длина нормализованного = " << vector_length(norm) << std::endl;

  // Составные операции
  Vec3 v3(1.0, 1.0, 1.0);
  std::cout << "\nv3 = " << v3 << std::endl;

  // Проверка через функции библиотеки
  Vec3 v5 = add(v1, v2);
  Vec3 v6 = multiply_scalar(v1, 3.0);
  std::cout << "\nЧерез функции библиотеки:" << std::endl;
  std::cout << "add_(v1, v2) = " << v5 << std::endl;
  std::cout << "multiply_scalar(v1, 3) = " << v6 << std::endl;

  return 0;
}
