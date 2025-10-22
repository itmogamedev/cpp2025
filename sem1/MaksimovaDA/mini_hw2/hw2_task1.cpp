#include <iostream>
#include <string>

std::string to_oct(int number) {
  std::string res_oct = "";
  if (number == 0) return "0";

  while (number > 0) {
    int remainder = number % 8;
    res_oct = std::to_string(remainder) + res_oct;
    number = number / 8;
  }

  return res_oct;
}

std::string to_hex(int number) {
  std::string res_hex = "";
  std::string hex_digits = "0123456789ABCDEF";

  if (number == 0) return "0";

  while (number > 0) {
    int remainder = number % 16;
    res_hex = hex_digits[remainder] + res_hex;
    number = number / 16;
  }
  return res_hex;
}

int main() {
  int number;

  std::cout << "enter the number in decimal: ";
  std::cin >> number;

  std::cout << "octal: " << to_oct(number) << std::endl;
  std::cout << "hexadecimal: " << to_hex(number) << std::endl;
}