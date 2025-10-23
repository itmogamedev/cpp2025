#include<iostream>
#include<cmath>

float compute_trapezoid_area(int a, int b, int c, int d) {
  int p = a + b + c + d;
  float h = std::sqrt(
    (p - 2 * a) * (p - 2 * b) * (p - 2 * b - 2 * d) * (p - 2 * b - 2 * c)
  ) / (2.0 * std::abs(b - a));
  return h * (a + b) / 2;
}

int main() {
  int a, b, c, d;
  std::cout << "Введите длину большого основания: ";
  std::cin >> a;
  std::cout << "Введите длину малого основания: ";
  std::cin >> b;
  std::cout << "Введите длины сторон: " << std::endl;
  std::cin >> c >> d;
  std::cout << std::endl << "Площадь трапеции: "
    << compute_trapezoid_area(a, b, c, d) << std::endl;

  return 0;
}
