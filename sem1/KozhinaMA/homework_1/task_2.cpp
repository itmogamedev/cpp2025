#include <iostream>

int main() {
  int storona1, storona2, visota, S;

  std::cout << "Enter the base1 of the trapezoid:" << std::endl;
  std::cin >> storona1;
  std::cout << "Enter the base2 of the trapezoid:" << std::endl;
  std::cin >> storona2;
  std::cout << "Enter the trapezoid height:" << std::endl;
  std::cin >> visota;
  if (storona1 > 0 and storona2 > 0 and visota > 0) {
    S = ((storona1 + storona2) / 2) * visota;
    std::cout << "S = " << S;
  }
}
