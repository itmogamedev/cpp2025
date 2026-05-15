#include <iostream>

int main() {
  setlocale(LC_ALL, "");
  unsigned int num;

  std::cout << "Введите натуральное число: " << std::endl;
  std::cin >> num;
  while (true) {
    if (num % 2 == 0) {
      num /= 2;
    } else {
      num = (num * 3 + 1) / 2;
    }

    if (num == 1) {
      std::cout << "гипотеза верна";
      break;
    }
  }
}
