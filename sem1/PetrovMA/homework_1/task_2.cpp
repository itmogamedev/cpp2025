

///<summary>Calculates the area of a trapezoid</summary>
float trapezoidArea(const float side_a, const float side_b, const float height) {
  return height * (side_a + side_b) / 2.f;
}

// Sample usage
#include <iostream>

int main() {
  float a, b, h;
  std::cout << "Enter side A: ";
  std::cin >> a;
  std::cout << "Enter side B: ";
  std::cin >> b;
  std::cout << "Enter height: ";
  std::cin >> h;
  std::cout << "Resulting area: " << trapezoidArea(a, b, h);
  return 0;
}
