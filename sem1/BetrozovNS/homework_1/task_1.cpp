#include <iostream>

int main() {
  int s;
  std::cout << "Длина стороны квадрата: ";
  std::cin >> s;
  int plos = s * s;
  std::cout << "Тогда площадь квадрата: " << plos << std::endl;

  return 0;
}
