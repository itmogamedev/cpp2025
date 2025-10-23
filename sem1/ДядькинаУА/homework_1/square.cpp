#include <iostream>

int main() {
  double side_length;
  std::cout << "Введите длину стороны квадрата: ";
  std::cin >> side_length;

  double area = side_length * side_length;
  std::cout << "Площадь квадрата: " << area << std::endl;

  return 0;
}