#include <iostream>

double squareAreaFromSide(double);

int main() {
  std::cout << "Input square side" << std::endl;
  double side;
  std::cin >> side;

  double squareArea = squareAreaFromSide(side);
  if (squareArea != -1) {
    std::cout << "Sqare area is " << squareArea;
  } else {
    std::cout << "Invalid side!";
  }
}

double squareAreaFromSide(double side) { return side > 0 ? side * side : -1; }
