#include <iostream>
#include <string>
#include <locale.h>

std::string ConvertToAnother(int ten, int to_another) //перевод в другую систему счисления, вплоть до 16-ричной включительно
{
  std::string alph = "0123456789ABCDEF";
  std::string new_valu = "";
    
  while (ten > 0) {
    int ost = ten % to_another;
    new_valu = alph[ost] + new_valu;
    ten /= to_another;
  }

  return new_valu;
}

int main()
{
  setlocale(LC_ALL, "Russian");

  int ten = 0;
  int to_another = 0;

  std::cout << "Введите число: ";
  std::cin >> ten;
  std::cout << "Введите новую систему счисления: ";
  std::cin >> to_another;
  std::cout << "Ваше число в новой системе счисления: ";
  std::cout << ConvertToAnother(ten, to_another) << std::endl;
}