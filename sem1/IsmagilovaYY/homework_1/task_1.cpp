// Реализовать функцию, которая возвращает подсчет площади квадрата
#include <iostream>

double squareArea(double side) { return side * side; }

int main() {
  double a;
  std::cin >> a;
  std::cout << squareArea(a);
  return 0;
}
