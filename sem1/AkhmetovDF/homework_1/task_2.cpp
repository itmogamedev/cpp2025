#include <iostream>

double trapeze(double a, double b, double h)
{
  return((a + b) / 2) * h;
}

int main()
{
  system("chcp 1251");
  system("cls");

  double a = 4;
  double b = 9;
  double h = 3;

  std::cout << "Площадь квадрата: " << trapeze(a, b, h) << std::endl;

  return 0;
}