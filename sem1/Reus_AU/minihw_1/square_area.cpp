#include <iostream>

float SquareArea(float side) {
  return side * side;
}

int main() {

  float side;
  std::cout << "Enter the length of the side of the square: ";
  std::cin >> side;
  std::cout << "Square area: " << SquareArea(side) << std::endl;

  return 0;
}
