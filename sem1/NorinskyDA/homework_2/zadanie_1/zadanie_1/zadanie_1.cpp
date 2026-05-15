#include <iomanip>
#include <iostream>

int main() {
  setlocale(0, "");
  int number;

  std::cout << "Введите десятичное число: ";
  std::cin >> number;

  std::cout << "Число в шестнадцатеричной СС: " << std::hex << number
            << std::endl;
  std::cout << "Число в восьмеричной СС: " << std::oct << number << std::endl;

  return 0;
}
