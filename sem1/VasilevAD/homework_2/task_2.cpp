#include <iostream>

int main() {
  setlocale(LC_ALL, "");
  int number;
  std::cout << "Введите натуральное число:" << std::endl;
  std::cin >> number;
  if (number > 0) {
    while (number != 1) {
      if (number % 2 == 0) {
        number = number/2;
      }
      else {
        number = ((number * 3) + 1) / 2;
      }
    }
    std::cout << "1 достигнуто" <<std::endl;
  }
  else {
    std::cout << "Неверный ввод" << std::endl;
  }
}