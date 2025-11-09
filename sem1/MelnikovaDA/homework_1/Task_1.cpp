#include <iostream>

int main() {
  float a;

  while (true) {
    std::cout << "Side of the square=";
    std::cin >> a;

    if (a <= 0) {
      std::cout << "Error" << std::endl;
    } else {
      std::cout << "Square area=" << a * a << std::endl;
    }
  }
}
