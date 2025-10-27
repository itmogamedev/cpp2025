#include <iostream>

int main() {
  double a, b, h;
  std::cout << "a" << std::endl;
  std::cin >> a;
  std::cout << "b" << std::endl;
  std::cin >> b;
  std::cout << "h" << std::endl;
  std::cin >> h;
  if (a > 0 and b > 0 and h > 0) {
    std::cout << ((a + b) / 2) * h;
  } else {
    std::cout << "write a number greater than 0" << std::endl;
  }
}
