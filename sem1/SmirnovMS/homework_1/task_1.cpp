#include <iostream>

float square(float a) { return a * a; }

int main() {
  std::cout << "Enter the side of the square:\n";

  float a = 0;  // Сторона квадрата

  std::cin >> a;

  float s = square(a);  // Площадь квадрата

  std::cout << "Square area = " << s;

  return 0;
}