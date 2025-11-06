#include <iostream>

double сalculateSquareArea(double side_length) {
  return side_length * side_length;
}

int main() {
  double side;
  std::cout << "Введите длину стороны квадрата " << std::endl;
  std::cin >> side;
  double area = сalculateSquareArea(side);
  std::cout << "Площадь квадрата со стороной " << side << " равна " << area << std::endl;
  return 0;
}