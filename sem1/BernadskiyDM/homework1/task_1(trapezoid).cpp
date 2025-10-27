#include <iostream>

int main() {
  int area, a, b, h;
  std::cout << "Enter the length of the first side of trapezoid:";
  std::cin >> a;

  std::cout << "Enter the length of the second side of trapezoid:";
  std::cin >> b;

  std::cout << "Enter the length of the trapezoid height:";
  std::cin >> h;

  area = (a + b) * h / 2;
  std::cout << "Square:" << area << std::endl;

  return 0;
}
