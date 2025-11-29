#include <iostream>

float trapezoidArea(float a, float b, float h) { return (a + b) / 2 * h; }

int main() {
  float trapezoid_side_top;
  float trapezoid_side_bottom;
  float trapezoid_height;

  std::cout << "Enter the top side of the trapezoid: ";
  std::cin >> trapezoid_side_top;
  std::cout << "Enter the bottom side of the trapezoid: ";
  std::cin >> trapezoid_side_bottom;
  std::cout << "Enter the height: ";
  std::cin >> trapezoid_height;
  std::cout << trapezoidArea(trapezoid_side_top, trapezoid_side_bottom,
                             trapezoid_height)
            << std::endl;

  return 0;
}
