#include <iostream>
#include <locale>
#include <string>
std::string decimalToHex(int decimal) {
  if (decimal == 0) return "0";

  std::string result = "";
  bool is_negative = false;

  if (decimal < 0) {
    is_negative = true;
    decimal = -decimal;
  }

  while (decimal > 0) {
    int remainder = decimal % 16;

    if (remainder < 10) {
      result = char('0' + remainder) + result;
    } else {
      result = char('A' + (remainder - 10)) + result;
    }

    decimal /= 16;
  }

  if (is_negative) {
    result = "-" + result;
  }

  return result;
}
std::string decimalToOctal(int decimal) {
  if (decimal == 0) return "0";

  std::string result = "";
  bool is_negative = false;

  if (decimal < 0) {
    is_negative = true;
    decimal = -decimal;
  }

  while (decimal > 0) {
    int remainder = decimal % 8;
    result = char('0' + remainder) + result;
    decimal /= 8;
  }

  if (is_negative) {
    result = "-" + result;
  }

  return result;
}
int main() {
  setlocale(LC_ALL, "");
  int input;
  std::cout << "Пожалйства, введите число: ";
  std::cin >> input;
  std::cout << "Шестнадцатиричная система счисления " << input << ": ";
  std::cout << decimalToHex(input) + '\n';
  std::cout << "Восьмиричная система счисления " << input << ": ";
  std::cout << decimalToOctal(input) + '\n';
  return 0;
}
