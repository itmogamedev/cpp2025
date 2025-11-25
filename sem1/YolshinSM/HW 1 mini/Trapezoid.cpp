#include <iostream>

double area(int a, int b, int h) { return (a + b) / 2.0 * h; }

int main() {
  int a = 0;
  int b = 0;
  int h = 0;
  std::cout << "Enter first base of the trapezoid: ";
  std::cin >> a;
  std::cout << "Enter second base of the trapezoid: ";
  std::cin >> b;
  std::cout << "Enter height of the trapezoid: ";
  std::cin >> h;
  std::cout << "Area of trapezoid: ";
  if (a == b) {
    std::cout << "This is not a trapezoid, dumbass!";
  } else {
    std::cout << area(a, b, h);
  }
}
