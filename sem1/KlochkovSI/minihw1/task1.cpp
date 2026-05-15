#include <iostream>

int plkv(int side_sq) { return side_sq * side_sq; }

int main() {
  int side_square = 0;
  std::cout << "Enter side length" << std::endl;
  std::cin >> side_square;
  std::cout << plkv(side_square);
  return 0;
}
