#include <locale.h>

#include <cstdlib>
#include <iostream>
double trapA(double a, double b, double h) { return ((a + b) / 2 * h); }
int main() {
  setlocale(LC_ALL, "Russian");
  double a = 0;
  double b = 0;
  double h = 0;
  std::cout << "Введите длину первого основания трапеции:\n";
  std::cin >> a;
  std::cout << "Введите длину второго основания квадрата:\n";
  std::cin >> b;
  std::cout << "Введите длину высоты трапеции:\n";
  std::cin >> h;
  std::cout << "Площадь трапеции равна = " << trapA(a, b, h) << std::endl;
}
