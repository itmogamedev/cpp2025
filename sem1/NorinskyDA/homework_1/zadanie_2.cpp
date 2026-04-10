
#include <iostream>

int main() {
  setlocale(0, "");

  float up_side, down_side, height;
  std::cout << "Для подсчёта площади трапеции введите следующие параметры: "
            << std::endl
            << "Длина верхнего основания: " << std::endl;
  std::cin >> up_side;
  std::cout << "Длина нижнего основания: " << std::endl;
  std::cin >> down_side;
  std::cout << "Высота: " << std::endl;
  std::cin >> height;
  std::cout << "Площадь трапеции: " << (up_side + down_side) / 2 * height
            << std::endl;

  return 0;
}
