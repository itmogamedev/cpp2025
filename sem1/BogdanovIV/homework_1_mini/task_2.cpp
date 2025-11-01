#include <iostream>

double areaOfTrapezoid(double top_side, double bottom_side, double height) {
  return (top_side + bottom_side) / 2 * height;
}

int main() {
  double top_side = 0, bottom_side = 0, height = 0;
  std::cout << "Input parametrs of trapezoid" << '\n';
  std::cout << "Top Side: ";
  std::cin >> top_side;
  std::cout << "Bottom Side: ";
  std::cin >> bottom_side;
  std::cout << "Height: ";
  std::cin >> height;

  std::cout << "Area: " << areaOfTrapezoid(top_side, bottom_side, height) << '\n';
  return 0;
}
