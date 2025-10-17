#include <iostream>

namespace geometry {

double Area(double base1, double base2, double height) {
  return (base1 + base2) * height / 2.0;
}

}  // namespace geometry

int main() {
  double base1 = 0.0;
  double base2 = 0.0;
  double height = 0.0;

  while (true) {
    std::cout << "Enter first base: ";
    std::cin >> base1;
    std::cout << "Enter second base: ";
    std::cin >> base2;
    std::cout << "Enter height: ";
    std::cin >> height;

    if ((base1 > 0.0) && (base2 > 0.0) && (height > 0.0)) {
      break;
    } else {
      std::cerr << "The length of the trapezoid should be >= 0" << std::endl;
    }
  }

  double area = geometry::Area(base1, base2, height);
  std::cout << "Area trapezoid: " << area << std::endl;

  return 0;
}
