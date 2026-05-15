// The area of trapezoid.
#include <iostream>

int main() {
  double height, first_side, second_side;
  std::cout << "Enter the height: ";
  std::cin >> height;
  std::cout << "Enter your first side: ";
  std::cin >> first_side;
  std::cout << "Enter your second side: ";
  std::cin >> second_side;
  std::cout << "The area of your trapezoid is: "
            << (0.5 * (first_side + second_side)) * height << std::endl;
  return 0;
}