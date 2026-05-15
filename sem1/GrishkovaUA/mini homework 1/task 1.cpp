#include <iostream>


double squareArea(double side) { return side * side; }

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

  double area = squareArea(length_side);
  std::cout << "Square area: " << area << std::endl;
  return 0;
}
