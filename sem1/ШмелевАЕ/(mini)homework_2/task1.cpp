#include <iostream>

int octNumber(int number) {
  std::cout.unsetf(std::ios::dec);
  std::cout.setf(std::ios::oct);
  return number;
}
int hexNumber(int number) {
  std::cout.unsetf(std::ios::dec);
  std::cout.setf(std::ios::hex);
  return number;
}
int main() {
  setlocale(LC_ALL, "rus");
  int dec_number;
  int measuring_system;
  std::cout << "Ведите число в десятичной системе счесления: ";
  std::cin >> dec_number;
  std::cout << "Укажите, в какую систему счесления перевести число (8/16): ";
  std::cin >> measuring_system;
  if (measuring_system == 8) {
    std::cout << "Ваше число: " << octNumber(dec_number);
  } else if (measuring_system == 16) {
    std::cout << "Ваше число: " << hexNumber(dec_number);
  } else {
    std::cout << "Программа переводит только в восьмиричную и "
                 "шестнадцатиричную системы.";
  }
  return 0;
}
