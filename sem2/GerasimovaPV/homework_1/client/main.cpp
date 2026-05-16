#include <iostream>
#include "../library/vectorLibrary.h"

int main()
{
  Vec3 a = {1, 2, 3 };
  Vec3 b = {6, 5, 4 };

  // Сложение
  Vec3 sum = a + b;
  std::cout << "a + b = " << sum << "\n";

  // Вычитание
  Vec3 diff = a - b;
  std::cout << "a - b = " << diff << "\n";

  // Скалярное умножение
  Vec3 scaled = a * 2.0f;
  std::cout << "a * 2 = " << scaled << "\n";

  // Скалярное произведение
  float dp = dot(a, b);
  std::cout << "dot(a, b) = " << dp << "\n";

  // Векторное произведение
  Vec3 cp = cross(a, b);
  std::cout << "cross(a, b) = " << cp << "\n";

  // Длина вектора
  float lenA = length(a);
  std::cout << "length(a) = " << lenA << "\n";

  // Нормализация
  Vec3 normA = norm(a);
  std::cout << "norm(a) = " << normA << "\n";

  // Длина нормализованного вектора
  std::cout << "length(norm(a)) = " << length(normA) << "\n";
}