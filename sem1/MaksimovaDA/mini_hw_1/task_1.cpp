#include <iostream>
int main() {
  int square = 0;
  std::cout << "side of the square: ";
  std::cin >> square;
  int s_square = square * square;
  std::cout << "S = ";
  std::cout << s_square << std::endl;
}