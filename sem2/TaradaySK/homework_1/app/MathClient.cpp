
#include <cstdlib>
#include <iostream>

#include "MathLibrary.h"

void UserInput(int* v, const std::string& name) {
  std::cout << "Введите координаты для " << name << " (x y z): ";
  std::cin >> v[0] >> v[1] >> v[2];
}
void PrintVector(const float* v, const std::string& label) {
  std::cout << label << ": (" << v[0] << ", " << v[1] << ", " << v[2] << ")\n";
}
int main() {
  std::setlocale(LC_ALL, "Russian");
  int vecA[3], vecB[3];
  float result[3];
  float Scalar;
  std::cout << "--- Работа с векторами ---\n";
  UserInput(vecA, "Вектора A");
  UserInput(vecB, "Вектора B");
  std::cout << "Введите скаляр для умножения: ";
  std::cin >> Scalar;
  std::cout << "--- Формулы ---\n";
  Add(vecA, vecB, result);
  PrintVector(result, "A+B");
  Subtract(vecA, vecB, result);
  PrintVector(result, "A-B");
  Multiply(vecA, Scalar, result);
  PrintVector(result, "Умножение A на скаляр");
  std::cout << "Скалярное произведение: " << Dot(vecA, vecB) << "\n";
  Cross(vecA, vecB, result);
  PrintVector(result, "Векторное произведение");
  std::cout << "Длина вектора A: " << GetLength(vecA) << "\n";
  Normalize(vecA, result);
  PrintVector(result, "Нормализованный вектор A");
  return 0;
}
