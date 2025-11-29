#include <iostream>
#include <string>

std::string ToBase(int number, int base) {
  if (number == 0) return "0";

  std::string result = "";
  const char digits[] = "0123456789ABCDEF";

  while (number > 0) {
    int remainder = number % base;
    result = digits[remainder] + result;
    number /= base;
  }

  return result;
}

int main() {
  int number;
  setlocale(LC_ALL, "Russian");
  std::cout << "Введите десятичное число: ";
  std::cin >> number;

  if (number < 0) {
    std::cout << "Введите неотрицательное число." << std::endl;
    return 1;
  }

  std::cout << "Шестнадцатеричное представление: " << ToBase(number, 16)
            << std::endl;
  std::cout << "Восьмеричное представление: " << ToBase(number, 8) << std::endl;

  return 0;
}
