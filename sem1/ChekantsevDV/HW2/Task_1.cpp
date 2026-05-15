#include <iostream>
#include <string>

int main() {
  setlocale(LC_ALL, "Rus");

  int variant;
  std::string new_chislo{};
  std::string new_chislo2{};
  const char alf[17] = {"0123456789ABCDEF"};

  std::cout << "Выберите систему счисления: " << std::endl;
  std::cout << "1. 8" << std::endl;
  std::cout << "2. 16" << std::endl;
  std::cin >> variant;

  switch (variant) {
    case 1:
      int chislo1;
      std::cout << "Вы выбрали восьмеричную систему счисления" << std::endl;
      std::cout << "Введите число: " << std::endl;
      std::cin >> chislo1;

      while (chislo1 > 0) {
        new_chislo = {std::to_string(chislo1 % 8) + new_chislo};
        chislo1 /= 8;
      }

      std::cout << new_chislo;
      break;

    case 2:
      int chislo2, per;
      std::cout << "Вы выбрали шестнадцатеричную систему счисления"
                << std::endl;
      std::cout << "Введите число: " << std::endl;
      std::cin >> chislo2;

      while (chislo2 > 0) {
        per = chislo2 % 16;
        chislo2 /= 16;
        new_chislo2 = {alf[per] + new_chislo2};
      }

      std::cout << new_chislo2;
      break;

    default:
      std::cout << "нет такого варианта";
      break;
  }
}
