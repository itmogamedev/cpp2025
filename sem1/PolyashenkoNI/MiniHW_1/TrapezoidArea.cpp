#include <iostream>

double trapezoidArea(double a, double b, double h) {
  if (a > 0 && b > 0 && h > 0) {
    std::cout << "Area of trapezoid = ";
    return (a + b) / 2.0 * h;
  } else {
    std::cout << "Unfortunately, you have been banned." << std::endl;
    std::exit(0);
  }
}

int main() {
  double a, b, h = 0;

  std::cout << "Enter the lower base of your trapezoid: ";
  std::cin >> a;
  std::cout << "Enter the upper base of your trapezoid: ";
  std::cin >> b;
  std::cout << "Enter the height of your trapezoid: ";
  std::cin >> h;

  std::cout << trapezoidArea(a, b, h)
            << std::endl;
  return 0;
}