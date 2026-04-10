#include <iostream>

int findSquareArea(int square_side) { return square_side * square_side; }

int main() {
  int square_side;
  std::cout << "Enter the side of the square: ";
  std::cin >> square_side;
  std::cout << '\n'
            << "The area of the square: " << findSquareArea(square_side);
  return 0;
}
