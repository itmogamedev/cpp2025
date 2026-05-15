#include <iostream>

int trapetzarea(int height, int a, int b) { return height * ((a + b) / 2); }

int main() {
  float height, a, b, area;
  std::cout << "this program calculates the area of your trapezoid!";
  std::cout << "\nheight: ";
  std::cin >> height;
  std::cout << "\na: ";
  std::cin >> a;
  std::cout << "\nb: ";
  std::cin >> b;
  area = trapetzarea(height, a, b);
  std::cout << "\narea = " << area;
  std::cout << std::endl;
  return 0;
}
