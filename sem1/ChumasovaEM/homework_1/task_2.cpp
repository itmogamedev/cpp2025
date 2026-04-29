#include <iostream>

int main() {
  float osn_first = 0;
  float osn_second = 0;
  float height = 0;

  while (true) {
    std::cout << "First base of the trapezoid: ";
    std::cin >> osn_first;

    std::cout << "Second base of the trapezoid: ";
    std::cin >> osn_second;

    std::cout << "Height: ";
    std::cin >> height;

    if (osn_first <= 0 || osn_second <= 0 || height <= 0) {
      std::cout << "Error" << std::endl;
    } else {
      std::cout << "Area of the trapezoid: "
                << ((osn_first + osn_second) / 2) * height << std::endl;
    }
  }
}
