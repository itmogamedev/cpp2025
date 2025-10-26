#include <iostream>

float trapezoidArea(float base_1_length, float base_2_length, float height)
{
  return (base_1_length + base_2_length) * height / 2;
}

int main() {
  float base_1_length, base_2_length, height;
  std::cout << "Enter the trapezoid first base length: ";
  std::cin >> base_1_length, 
  std::cout << "Enter the trapezoid second base length: ";
  std::cin >> base_2_length, 
  std::cout << "Enter the trapezoid height: ";
  std::cin >> height;
  std::cout << "Trapezoid area: " << trapezoidArea(base_1_length, base_2_length, height) << std::endl;
  return 0;
}