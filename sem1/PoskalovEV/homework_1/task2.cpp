float area_trapezoid(float a, float b, float height) {
  return height * (a + b) / 2.;
}

/* Реализовать функцию, которая возвращает подсчет площади трапеции. */

#include <iostream>

int main() {
  std::cout << area_trapezoid(2, 3, 3) << std::endl;
  return 0;
}