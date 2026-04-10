#include <iostream>

double areaOfSquare(double side) {
  return side * side;
}

int main() {
  double side = 0;
  std::cout << "Input square side: ";
  std::cin >> side;
  std::cout << "Square area: " << areaOfSquare(side) << '\n';

  return 0;
}
