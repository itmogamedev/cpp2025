#include <iostream>

namespace geometry {
double SquareArea(double side) { return side * side; }
}  // namespace geometry

int main() {
  double length_side = 0.0;
  while (true) {
    std::cout << "Enter the side of the square: ";
    std::cin >> length_side;

    if (length_side > 0.0) {
      break;
    } else {
      std::cerr << "The length of the square should be >=0 " << std::endl;
    }
  }

  double area = geometry::SquareArea(length_side);
  std::cout << "Square area: " << area << std::endl;
  return 0;
}
