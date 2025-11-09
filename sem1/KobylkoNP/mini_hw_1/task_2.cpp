#include <iostream>

int main() {
  float b;
  float c;
  float h;
  std::cout << "Enter the first side of the trapezoid: ";
  std::cin >> b;
  std::cout << "Enter the second side of the trapezoid: ";
  std::cin >> c;
  std::cout << "Enter the height of the trapezoid: ";
  std::cin >> h;
  std::cout << "The area of the trapezoid is: ";
  std::cout << (b + c) / 2 * h;
}