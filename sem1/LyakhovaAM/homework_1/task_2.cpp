#include <iostream>

float findTrapezoidArea(float trapezoid_base1, float trapezoid_base2,
                        float trapezoid_height) {
  return (trapezoid_base1 + trapezoid_base2) * trapezoid_height / 2;
}

int main() {
  float trapezoid_base1, trapezoid_base2, trapezoid_height;
  std::cout << "Enter bases of the trapezoid: ";
  std::cin >> trapezoid_base1 >> trapezoid_base2;
  std::cout << '\n' << "Enter the height of the trapezoid: ";
  std::cin >> trapezoid_height;
  std::cout << '\n'
            << "The area of the trapezoid: "
            << findTrapezoidArea(trapezoid_base1, trapezoid_base2,
                                 trapezoid_height);
  return 0;
}
