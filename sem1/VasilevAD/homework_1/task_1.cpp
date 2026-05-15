#include <iostream>

int main()
{
  double side;
  std::cout << "Введите длину стороны" << std::endl;
  std::cin >> side;
  std::cout << "Площадь квадрата:" << side*side << std::endl;
  return 0;
}