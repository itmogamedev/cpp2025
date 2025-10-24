#include <iostream>

int main() {
  float sq_s = 0;

  while (true) {
    std::cout << "side of the square: ";
    std::cin >> sq_s;

    if (sq_s <= 0) {
      std::cout << "Error" << std::endl;
    } else {
      std::cout << "square: " << sq_s * sq_s << std::endl;
    }
  }
}
