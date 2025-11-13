#include <iostream>

int main() {
  double a;
  double b;
  double h;

  std::cout << "Введите длину первого основания: ";
  std::cin >> a;

  std::cout << "Введите длину второго основания: ";
  std::cin >> b;

  std::cout << "Введите высоту трапеции: ";
  std::cin >> h;

  double area = (a + b) * h / 2.0;
  std::cout << "Площадь трапеции: " << area << std::endl;

  return 0;
}