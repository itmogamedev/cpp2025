///<summary>Calculates area of a square</summary>
float squareArea(float side) {
  return side * side;
}

// Sample usage:
#include <iostream>

int main() {
  float side;
  std::cout << "Enter the side of a square: ";
  std::cin >> side;
  std::cout << "Resulting area: " << squareArea(side);
  return 0;
}
