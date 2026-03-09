#include <iostream>
#include <string>

std::string oct(int num) {
  std::string oct_num = "";

  while (num != 0) {
    oct_num = std::to_string(num % 8) + oct_num;
    num /= 8;
  }
  return oct_num;
}

std::string hex(int num) {
  std::string hex_num = "";
  const char hex_mas[] = "0123456789ABCDEF";

  while (num != 0) {
    hex_num = hex_mas[num % 16] + hex_num;
    num /= 16;
  }
  return hex_num;
}

int main() {
  setlocale(LC_ALL, "");
  int num;

  std::cin >> num;

  std::cout << "Введённое число в восьмиричной системе счисления: " << oct(num)
            << std::endl;
  std::cout << "Введённое число в шестнадцатиричной системе счисления: "
            << hex(num);
}
