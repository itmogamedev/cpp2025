#include <iostream>

int main() {
  int base_top = 0;
  int base_bottom = 0;
  int height = 0;
  double area = 0.0;
  std::cout << "please enter the top base, bottom base and height of the "
               "trapezoid :\n";
  std::cin >> base_top;
  std::cin >> base_bottom;
  std::cin >> height;

  while (base_top < 0) {
    std::cout << "please enter a positive top base of the trapezoid, the "
                 "previous one was less then zero : ";
    std::cin >> base_top;
  }
  while (base_bottom < 0) {
    std::cout << "please enter a positive bottom base of the trapezoid, the "
                 "previous one was less then zero : ";
    std::cin >> base_bottom;
  }
  while (height < 0) {
    std::cout << "please enter a positive height of the trapezoid, the "
                 "previous one was less then zero : ";
    std::cin >> height;
  }
  area = height * (base_top + base_bottom) / 2.0;
  std::cout << "the area of the trapezoid is: " << area;
}
