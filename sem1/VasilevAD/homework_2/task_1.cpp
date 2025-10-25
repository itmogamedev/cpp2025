#include <iostream>
using namespace std;

int main() {
  setlocale(LC_ALL, "");
  int N;
  int des;
  string vosm = "";
  string shest = "";
  std:: cout << "Что вы хотите сделать?"
  << std::endl << "1. Перевести в восьмиричную систему"
  << std::endl << "2. Перевести в шестнадцатиричную систему" << std::endl;
  std::cin >> N;
  if (N == 1) {
    std::cout << "Введите число" << std::endl;
    std::cin >> des;
    while (des > 0)
    {
      vosm = to_string(des%8) + vosm;
      des = des/8;
    }
    std::cout << vosm << std::endl;
  }
  else if (N == 2) {
    std::cout << "Введите число" << std::endl;
    std::cin >> des;
    std::string alphabet = "0123456789ABCDEF";
    while (des > 0)
    {
      shest = alphabet[des % 16] + shest;
      des = des/16;
    }
    std::cout << shest << std::endl;
  }
  else {
    std:: cout << "Данный вариант отсутствует";
  }
  return 0;
}
