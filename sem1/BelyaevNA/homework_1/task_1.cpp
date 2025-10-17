#include <iostream>
int side = 0;
int square = 0;
int calc_square(int side) { return side * side; }
int main() {
  std::cin >> side;
  square = calc_square(side);
  std::cout << square;
}
