#include <iostream>

double square(double side) { return side * side; }

int main(void) {
  int side;
  std::cout << "Side: ";
  std::cin >> side;
  std::cout << square(side);
}
