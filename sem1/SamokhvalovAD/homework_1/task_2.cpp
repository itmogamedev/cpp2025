#include <iostream>

float trap(int side_a, int side_b, int height) {
  return 0.5 * (side_a + side_b) * height;
}

int main() {
  int side_a, side_b, height;
  std::cout << "Enter the lengths of the two parallel sides and the height of "
               "the trapezoid: ";
  std::cin >> side_a >> side_b >> height;
  std::cout << "The area of the trapezoid is " << trap(side_a, side_b, height)
            << "\n";
  return 0;
}