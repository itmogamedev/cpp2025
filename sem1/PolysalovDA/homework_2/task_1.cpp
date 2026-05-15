#include <iostream>
#include <string>

std::string DecimalToOctal(int decimal_number) {
  // Обрабатываем специальный случай - ноль
  if (decimal_number == 0) {
    return "0";
  }

  // Основная рекурсия (только для чисел > 0)
  if (decimal_number < 8) {
    return std::to_string(decimal_number);
  }

  std::string result = DecimalToOctal(decimal_number / 8);
  result += std::to_string(decimal_number % 8);
  return result;
}

std::string DecimalToHex(int decimal_number) {
  std::string alphabet = "0123456789ABCDEF";
  if (decimal_number == 0) {
    return "0";
  }
  if (decimal_number < 16) {
    return std::string() + alphabet[decimal_number];
  }

  std::string result = DecimalToHex(decimal_number / 16);
  result += alphabet[decimal_number % 16];
  return result;
}

int main() {
  while (true) {
    int entered_number;

    std::cout << "Введите десятичное число: ";
    std::cin >> entered_number;

    std::cout << "Восьмеричное: ";
    std::cout << DecimalToOctal(entered_number) << std::endl;

    std::cout << "Шестнадцатиричное: ";
    std::cout << DecimalToHex(entered_number) << std::endl;
  }
}