#include <iostream>

double trapezoidArea(double a, double b, double h) { return (a + b) / 2 * h; }

int main() {
  double a, b, h;
  setlocale(LC_ALL, "Russian");
  std::cout << "Введите длину первого основания трапеции: ";
  std::cin >> a;
  std::cout << "Введите длину второго основания трапеции: ";
  std::cin >> b;
  std::cout << "Введите высоту трапеции: ";
  std::cin >> h;

  if (a < 0 || b < 0 || h < 0) {
    std::cout << "Длины оснований и высота должны быть неотрицательными."
              << std::endl;
    return 1;
  }

  std::cout << "Площадь трапеции: " << trapezoidArea(a, b, h) << std::endl;
  return 0;
}
