#include <iostream>

namespace geometry {

double TrapezoidArea(double a, double b, double h) {
  if (a <= 0 || b <= 0 || h <= 0) {
    std::cout << "ERROR";
    return 0;
  }
  return (a + b) / 2 * h;
}

}  // namespace geometry

int main() {
  double a;
  double b;
  double h;

  std::cout << "a: ";
  std::cin >> a;

  std::cout << "b: ";
  std::cin >> b;

  std::cout << "h: ";
  std::cin >> h;

  double area = geometry::TrapezoidArea(a, b, h);
  if (area > 0) {
    std::cout << "Area trapezoid = " << area << std::endl;
  }

  return 0;
}
