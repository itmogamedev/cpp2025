#include <iostream>

double trapezoid(double base1, double base2, double height) {
  return (base1 + base2) / 2 * height;
}

int main(void) {
  int height, base1, base2;
  std::cout << "BaseA: ";
  std::cin >> base1;
  std::cout << "BaseB: ";
  std::cin >> base2;
  std::cout << "Height: ";
  std::cin >> height;
  std::cout << trapezoid(base1, base2, height);
}
