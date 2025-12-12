#include <iostream>
#include <limits>

int main() {
  int number;

  std::cout << "Введите десятичное число: ";

  if (!(std::cin >> number)) {
    std::cout << "Ошибка: введено не число.\n";
    return 1;
  }

  if (number < 0) {
    std::cout << "Программа работает только с неотрицательными числами.\n";
    return 1;
  }

  std::ios_base::fmtflags original_flags = std::cout.flags();

  std::cout << "Десятичное: " << std::dec << number << '\n';
  std::cout << "Восьмеричное: " << std::oct << number << '\n';
  std::cout << "Шестнадцатеричное: " << std::hex << number << '\n';

  std::cout.flags(original_flags);

  return 0;
}
