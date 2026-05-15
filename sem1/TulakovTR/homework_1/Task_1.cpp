#include <iostream>

void main()
{
  setlocale(LC_ALL, "ru");
  float a;
  float s;
  std::cout << "введи число:" << std::endl;
  std::cin >> a;
  s = a * a;
  std::cout << "Площадь равна=" << s << std:: endl;
}