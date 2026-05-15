#include <iostream>

int square(int a) { return a * a; }

int main() {
  int square_area;
  std::cout << "Please, type number for area of the square" << std::endl;
  std::cin >> square_area;
  std::cout << "Square area = " << square(square_area) << std::endl;
  return 0;
}
