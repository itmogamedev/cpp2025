#include <iostream>

int main()
{
  float base_one = 0.0f;
  float base_two = 0.0f;
  float height = 0.0f;

  std::cout << "The bases of the trapezoid equal: ";
  std::cin >> base_one >> base_two;
  std::cout << "The height of the trapezoid equals: ";
  std::cin >> height;

  const float area = (base_one + base_two) / 2.0f * height;
  std::cout << "The area of the trapezoid equals " << area << std::endl;

  return 0;
}