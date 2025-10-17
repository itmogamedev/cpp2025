#include <iostream>

int main() {
  float squareSide;
  setlocale(LC_ALL, "RU");
  std::cout << "укажите сторону квадрата" << std::endl;
  std::cin >> squareSide;
  std::cout << "Площадь равна этого квадрата равна  " << squareSide * squareSide
            << std::endl;
  std::cout << "Для закрытия программы нажмите любую клавишу и enter";
  char x;
  std::cin >> x;
  return 0;
}
