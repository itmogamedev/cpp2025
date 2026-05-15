#include <iostream>
#include <locale>

float sOfSquare(float func_float);

int main() {
  setlocale(LC_CTYPE, "Russian");
  float input_float = 0;
  std::cout << "Введите сторону квадрата: ";
  std::cin >> input_float;
  std::cout << "Площадь квадрата: " << sOfSquare(input_float);
  return 0;
}

float sOfSquare(float func_float) {
  return func_float * func_float;
}
