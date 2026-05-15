#include <iostream>

int squareArea(int side_sq) { return side_sq * side_sq; }

int main() {
  int side_square = 24;
  std::cout << squareArea(side_square);
  return 0;
}
