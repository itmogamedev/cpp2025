#include <locale.h>

#include <cstdlib>
#include <iostream>
double squareA(double a) { return (a * a); }
int main() {
  setlocale(LC_ALL, "Russian");
  double a = 0;
  std::cout << "Введите длину стороны квадрата:\n";
  std::cin >> a;
  std::cout << "Площадь квадрата равна = " << squareA(a);
}
