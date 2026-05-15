#include <iostream>

int main() {
  double side;
  std::cout << "Введите длину стороны квадрата: ";
  std::cin >> side;

  double area = side * side;
  std::cout << "Площадь квадрата: " << area << std::endl;

  return 0;
}