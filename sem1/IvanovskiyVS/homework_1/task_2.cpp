
// Минидомашка 1
// Задача 2: Реализовать функцию, которая возвращает подсчет площади трапеции.

#include <iostream>
float trapezoidArea(float larger_trapezoid_base, float smaller_trapezoid_base,
                    float trapezoid_height) {
  return ((larger_trapezoid_base + smaller_trapezoid_base) * trapezoid_height /
          2);
}
int main() {
  std::cout << "Enter the length of larger trapezoid base: ";
  float larger_trapezoid_base;
  std::cin >> larger_trapezoid_base;
  std::cout << "Enter the length of smaller trapezoid base: ";
  float smaller_trapezoid_base;
  std::cin >> smaller_trapezoid_base;
  std::cout << "Enter the trapezoid height: ";
  float trapezoid_height;
  std::cin >> trapezoid_height;
  std::cout << "\nThe trapecoid area is "
            << trapezoidArea(larger_trapezoid_base, smaller_trapezoid_base,
                             trapezoid_height)
            << std::endl;
}
