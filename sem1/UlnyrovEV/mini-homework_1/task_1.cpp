#include <iostream>

double areaOfSquare(double side) { return side * side; }

int main() {
  double side;
  std::cout << "Enter the side of the square: ";
  std::cin >> side;

  std::cout << "Square area is: " << areaOfSquare(side) << std::endl;
  return 0;
}
