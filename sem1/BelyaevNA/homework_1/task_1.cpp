#include <iostream>
int side = 0;
int square = 0;
int calcS(int side) { return side * side; }
int main() {
  std::cin >> side;
  square = calcS(side);
  std::cout << square;
}
