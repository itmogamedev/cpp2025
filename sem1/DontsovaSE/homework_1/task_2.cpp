#include <iostream>

double calculateTrapezoidArea(double base_a, double base_b, double height) {
  return (base_a + base_b) * height / 2.0;
}

int main() {
  double base_a, base_b, height;

  std::cout << "Введите длину первого основания (a): ";
  std::cin >> base_a;
  if (std::cin.fail()) {
    std::cout << "Ошибка: введите число!" << std::endl;
    return 1;
  }

  std::cout << "Введите длину второго основания (b): ";
  std::cin >> base_b;
  if (std::cin.fail()) {
    std::cout << "Ошибка: введите число!" << std::endl;
    return 1;
  }

  std::cout << "Введите высоту трапеции (h): ";
  std::cin >> height;
  if (std::cin.fail()) {
    std::cout << "Ошибка: введите число!" << std::endl;
    return 1;
  }

  if (base_a <= 0 || base_b <= 0 || height <= 0) {
    std::cout << "Ошибка: все значения должны быть положительными!"
              << std::endl;
    return 1;
  }

  double area = calculateTrapezoidArea(base_a, base_b, height);

  std::cout << "Площадь трапеции: " << area << std::endl;

  return 0;
}
