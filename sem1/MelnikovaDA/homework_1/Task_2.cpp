#include <iostream>

int main() {
  float a, b, h;

  while (true) {
    std::cout << "The base and height of the trapezoid:" << std::endl;
    std::cout << "lower base=";
    std::cin >> a;
    std::cout << "upper base=";
    std::cin >> b;
    std::cout << "height=";
    std::cin >> h;

    if (a > 0 and b > 0 and h > 0) {
      std::cout << "trapezoid area=" << (a + b) * h / 2 << std::endl;
    } else {
      std::cout << "error" << std::endl;
    }
  }
}
