#include <iostream>

double calculateSquareArea(double side_length) {
  return side_length * side_length;
}

int main() {
  double side;

  std::cout << "Введите длину стороны квадрата: ";
  std::cin >> side;

  if (std::cin.fail()) {
    std::cout << "Ошибка: введите число!" << std::endl;
    return 1;
  }

  if (side < 0) {
    std::cout << "Ошибка: длина не может быть отрицательной!" << std::endl;
    return 1;
  }

  double area = calculateSquareArea(side);
  std::cout << "Площадь квадрата: " << area << std::endl;

  return 0;
}
