#include <iostream>

double areaOfTrapezoid() {
  double a;
  double b;
  double h;
  std::cout << "Please, enter the sides of the trapezoid: ";
  std::cin >> a >> b;
  std::cout << "Please, enter the height of the trapezoid: ";
  std::cin >> h;
  return ((a + b) / 2.0) * h;
}

int main() { std::cout << areaOfTrapezoid(); }
