#include <iostream>

double areaOfTrapezoid(double longerBase, double shorterBase, double height) {
  return (longerBase + shorterBase) * height / 2.0;
}

int main() {
  double a, b, h;
  std::cout << "Enter the longer base: ";
  std::cin >> a;
  std::cout << "Enter the shorter base: ";
  std::cin >> b;
  std::cout << "Enter the height: ";
  std::cin >> h;

  std::cout << "Trapezoid area is: " << areaOfTrapezoid(a, b, h) << std::endl;
  return 0;
