#include <iostream>

int squareArea(int a) { return a * a; }

int main() {
  int square_side;

  std::cout << "Enter the side of the square: ";
  std::cin >> square_side;
  std::cout << squareArea(square_side) << std::endl;

  return 0;
}
