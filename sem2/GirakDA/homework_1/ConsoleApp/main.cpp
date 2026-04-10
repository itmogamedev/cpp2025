#include <iostream>

#include "..\MathLibrary\MathLibrary.h"

int runTests() {
  setlocale(LC_ALL, "RUS");
  Vec3 v1(1.0, 5.0, 3.0);
  Vec3 v2(4.0, 5.0, 3.0);
  Vec3 v3(2.0, 0.0, 0.0);
  std::cout << "Вектор v1 = " << v1 << std::endl;
  std::cout << "Вектор v2 = " << v2 << std::endl;
  std::cout << "Вектор v3 = " << v3 << std::endl;
  std::cout << std::endl;
  Vec3 sum = v1 + v2;
  std::cout << "v1 + v2 (1способ) = " << sum << std::endl;
  std::cout << "v1 + v2 (2способ) = " << addVectors(v1, v2) << std::endl;
  Vec3 diff = v2 - v1;
  std::cout << "v2 - v1 (1способ) = " << diff << std::endl;
  std::cout << "v2 - v1 (2способ) = " << subtractVectors(v2, v1) << std::endl;
  int scalar = 5;
  Vec3 scaled = v1 * scalar;
  std::cout << "v1 * (1способ) " << scalar << " = " << scaled << std::endl;
  std::cout << scalar << " (1способ) * v1 = " << scalar * v1 << std::endl;
  std::cout << "v1 * (2способ)" << scalar << " = "
            << multiplyByScalar(v1, scalar) << std::endl;
  double dot = dotProduct(v1, v2);
  std::cout << "Скалярное произведение v1 и v2 = " << dot << std::endl;
  Vec3 cross = crossProduct(v1, v2);
  std::cout << "Векторное произведение v1 и v2 = " << cross << std::endl;
  std::cout << "Длина вектора v1 = " << vectorLength(v1) << std::endl;
  std::cout << "Длина вектора v3 = " << vectorLength(v3) << std::endl;
  Vec3 normalized = normalizeVector(v1);
  std::cout << "Нормализованный v1 = " << normalized << std::endl;
  return 0;
}

int main() {
  runTests();
  return 0;
}
