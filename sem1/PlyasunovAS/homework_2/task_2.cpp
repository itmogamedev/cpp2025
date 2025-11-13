#include <iostream>

double areaOfTrapezoid(double a, double b, double h) {
  return (a + b) * h / 2.0;
}

int main() {
  double a, b, h;

  std::cout << "Vvedite dliny pervogo ocnovania (a): ";
  std::cin >> a;
  std::cout << "Vvedite dliny vtorogo ocnovania (b): ";
  std::cin >> b;
  std::cout << "Vvedite visoty trapetshii (h): ";
  std::cin >> h;

  double result = areaOfTrapezoid(a, b, h);
  std::cout << "ploshad trapth: " << result << std::endl;

  return 0;
}