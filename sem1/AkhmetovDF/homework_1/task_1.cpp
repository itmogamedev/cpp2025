#include <iostream>

double squareA(double x)
{
  return(x * x);
}

int main()
{
  system("chcp 1251");
  system("cls");

  double x = 10;

  std::cout << "Площадь квадрата: " << squareA(x) << std::endl;

  return 0;
}