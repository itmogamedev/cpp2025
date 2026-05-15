#include <format>
#include <iostream>
#include <locale>
#include <string>

std::string toOct(int num_input);
std::string toHex(int num_input);

int main() {
  std::setlocale(LC_CTYPE, "Russian");
  int input_int = 0;

  std::cout << "Введите число в 10-ой системе счисления: ";
  std::cin >> input_int;

  std::cout << "В 8-ой системе счисления: " << toOct(input_int) << "\n";
  std::cout << "В 16-ой системе счисления: " << toHex(input_int) << "\n";

  return 0;
}

std::string toOct(int func_int) {
  return std::format("{:o}", func_int);
}

std::string toHex(int func_int) {
  return std::format("{:x}", func_int);
}
