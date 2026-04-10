#include <iostream>

namespace geometry {

double SquareArea(double side) { return side * side; }

}  // namespace geometry

int main() {
  double side;
  std::cout << "Side: ";
  std::cin >> side;

  if (side <= 0) {
    std::cout << "Number must be > 0" << std::endl;
    return 0;
  }

  double area = geometry::SquareArea(side);
  std::cout << "Square area = " << area << std::endl;

  return 0;
}
