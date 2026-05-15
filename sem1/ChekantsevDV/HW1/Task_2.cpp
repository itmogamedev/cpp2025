#include <iostream>

int main() {
  float base1, base2, height;
  setlocale(LC_ALL, "Rus");
  std::cout << "Введите длину первого основания трапеции: ";
  std::cin >> base1;
  std::cout << "Введите длину второго основания трапеции: ";
  std::cin >> base2;
  std::cout << "Введите длину высоты трапеции: ";
  std::cin >> height;
  if (base1 * base2 * height > 0) {
    std::cout << "Площадь трапеции равна: " << (base1 + base2) / 2 * height
              << std::endl;
  } else {
    std::cout << "Введена(ы) неверное(ые) значение(я)";
  }
}
