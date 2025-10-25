#include <iostream>

int main() {
  int side = 0;
  int result = 0;

  while (true) {
    std::cout << "Enter the length of the side of the square: " << std::endl;
    std::cin >> side;

    if (side <= 0) {
      std::cout << "There is no such square!" << std::endl;
    } else {
      result = side * side;
      std::cout << "Square area: " << result << std::endl;
    }

    std::cout << "---------------------------------------------" << std::endl;
  }
}
