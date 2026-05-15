#include <iostream>

int main() {
  setlocale(0, "");
  float side;
  std::cout << "Введите сторону квадрата:" << std::endl;
  std::cin >> side;
  if (side >= 0)
    std::cout << "Площадь: " << side * side << std::endl;
  else
    std::cout << "Некорректная длина" << std::endl;

  return 0;
}
