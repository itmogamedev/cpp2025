// Реализовать функцию, которая возвращает подсчет площади трапеции
#include <iostream>

double trapezoidArea(double base1, double base2, double height) {
  return (base1 + base2) * height / 2;
}

int main() {
  double base_1;
  double base_2;
  double height;

  std::cin >> base_1;
  std::cin >> base_2;
  std::cin >> height;
  std::cout << trapezoidArea(base_1, base_2, height);
  return 0;
}
