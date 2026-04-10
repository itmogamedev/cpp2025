#include <iostream>

double сalculateTrapezoidArea(double base_1, double base_2, double height) {
  return ((base_1 + base_2) / 2) * height;
}

int main() {
  double base_a;
  double base_b;
  double height;
  std::cout << "Введите длину основания A: ";
  std::cin >> base_a;

  std::cout << "Введите длину основания B: ";
  std::cin >> base_b;

  std::cout << "Введите высоту трапеции: ";
  std::cin >> height;
  double area = сalculateTrapezoidArea(base_a, base_b, height);
  std::cout << "Значение площади трапеции: " << area << std:: endl;
  return 0;
}
