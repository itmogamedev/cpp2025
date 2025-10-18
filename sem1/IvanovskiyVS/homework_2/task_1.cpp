
// Минидомашка 2
// Задача 1: Реализовать функцию преобразования из десятичного числа в
// шестнадцатеричную и восьмеричную систему счисления.
#include <iostream>

std::string toHexadecimal(int dec_number) {
  std::string hex_number;
  while (dec_number != 0) {
    if (dec_number % 16 > 9) {
      hex_number = (char)(dec_number % 16 + 55) + hex_number;
    } else {
      hex_number = (char)(dec_number % 16 + 48) + hex_number;
    }
    dec_number /= 16;
  }
  return hex_number;
}

std::string toOctal(int dec_number) {
  std::string oct_number;
  while (dec_number != 0) {
    oct_number = (char)((dec_number % 8) + 48) + oct_number;
    dec_number /= 8;
  }
  return oct_number;
}

int main() {
  int entered_number;
  std::cout << "Please, enter the number: ";
  while (true) {
    std::cin >> entered_number;
    std::cout << "The entered number in the hexadecimal system: "
              << toHexadecimal(entered_number) << std::endl;
    std::cout << "The entered number in the octal system: "
              << toOctal(entered_number) << std::endl;
    std::cout << "\nPlease, enter the new number: ";
  }
  return 0;
}
