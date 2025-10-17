#include <iostream>
int side = 0;
int square = 0;
int calc_S(int side) { return side * side; }
int main() {
  std::cin >> side;
  square = calc_S(side);
  std::cout << square;
}
