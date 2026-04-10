#include <iostream>

int main() {
  setlocale(LC_ALL, "Russian");
  int a;

  std::cout << "Введите десятичное число: ";
  std::cin >> a;

  std::cout << "Шестнадцатеричное число: " << std::hex << a << std::endl;
  std::cout << "Восьмеричное число: " << std::oct << a << std::endl;

  return 0;
}
