#include <iostream>

double trapezoid(double a, double b, double h) { return (a + b) * h / 2; }

int main() {
  setlocale(LC_ALL, "Russian");
  double a, b, h;

  std::cout << "¬ведите длины оснований и высоту трапеции(a b h): ";
  std::cin >> a >> b >> h;

  double s = trapezoid(a, b, h);
  std::cout << "ѕлощадь трапеции: " << s << std::endl;

  return 0;
}
