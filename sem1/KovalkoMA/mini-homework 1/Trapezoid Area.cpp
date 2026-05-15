#include <iostream>

double calc_trapezoid_area(double a, double b, double h) {
  return 0.5 * (a + b) * h;
}

int main() {
  double a = 0.0;
  double b = 0.0;
  double h = 0.0;

  std::cout << "Enter length of the bases and the height of your trapezoid: ";
  std::cin >> a >> b >> h;
  double area = calc_trapezoid_area(a, b, h);
  std::cout << "The area of your trapezoid is: " << area << std::endl;
  return 0;
}
