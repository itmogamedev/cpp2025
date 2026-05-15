#include <iostream>

double getTrapezoidArea(double, double, double);

int main() {
  std::cout << "Input first side, second side and height of the trapezoid"
            << std::endl;
  double sideA, sideB, height;
  std::cin >> sideA >> sideB >> height;

  double trapezoidArea = getTrapezoidArea(sideA, sideB, height);
  if (trapezoidArea != -1) {
    std::cout << "Trapezoid area is " << trapezoidArea;
  } else {
    std::cout << "Invalid data!";
  }
}

double getTrapezoidArea(double sideA, double sideB, double height) {
  return (sideA > 0 && sideB > 0 && height > 0) ? (sideA + sideB) / 2 * height : -1;
}