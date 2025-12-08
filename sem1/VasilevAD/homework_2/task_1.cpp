#include <iostream>

int main() {
  int N;
  int des;
  std::string num;
  std::string alphabet = "0123456789ABCDEF";
  std:: cout << "Что вы хотите сделать?"
  << std::endl << "1. Перевести в восьмиричную систему"
  << std::endl << "2. Перевести в шестнадцатиричную систему" << std::endl;
  std::cin >> N;
  if (N == 1) {
    std::cout << "Введите число" << std::endl;
    std::cin >> des;
    while (des > 0)
    {
      num = alphabet[des%8] + num;
      des = des/8;
    }
    std::cout << num << std::endl;
  }
  else if (N == 2) {
    std::cout << "Введите число" << std::endl;
    std::cin >> des;
    while (des > 0)
    {
      num = alphabet[des % 16] + num;
      des = des/16;
    }
    std::cout << num << std::endl;
  }
  else {
    std:: cout << "Данный вариант отсутствует";
  }
  return 0;
}