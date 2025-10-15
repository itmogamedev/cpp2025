#include <iostream>

int main() {
  setlocale(LC_ALL, "RU");
  float high;
  float osn1;
  float osn2;
  std::cout << "укажите высоту" << std::endl;
  std::cin >> high;
  std::cout << "укажите основание 1" << std::endl;
  std::cin >> osn1;
  std::cout << "укажите основание 2" << std::endl;
  std::cin >> osn2;
  std::cout << "Площадь равна  " << (osn1 + osn2) / 2 * high << std::endl;
  std::cout << "Для закрытия программы нажмите любую клавишу и enter";
  char x;
  std::cin >> x;
  return 0;
}
