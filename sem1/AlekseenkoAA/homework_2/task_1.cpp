// task_1.cpp : преобразование из десятичной в шестнадцатеричную и восьмеричную
// систему счисления
#include <format> // ВНИМАНИЕ!!! Компиляция происходит для c++ 20+
#include <iostream>
#include <limits>
#include <string>

std::string dec2Hex(int a) { return std::format("{:0x}", a); }

std::string dec2Oct(int a) { return std::format("{:o}", a); }

int main() {
  // std::setlocale(LC_CTYPE, "Russian"); // На двух разных компах почему c++
  // работает по разному: один не выводит русский язык с setlocal(), а другой
  // выводит русский только без setlocale()
  /* Программа перевода из система в систему */
  std::cout << "Тест функций перевода числе в разные системы счисления \n";
  int sample_a;
  std::cout << "Число в десятичной системе счисление: ";
  std::cin >> sample_a;
  std::cout << "Число в шестнадцатеричной системе счисление:" << dec2Hex(sample_a) << "\n";
  std::cout << "Число в восмиричной системе счисление:" << dec2Oct(sample_a) << "\n";
  return 0;
}
