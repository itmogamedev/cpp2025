
#include <iostream>

int main() {
  setlocale(0, "");
  int num;
  std::cout << "Ведите натуральное число:" << std::endl;
  std::cin >> num;
  if (num > 0) {
    while (num != 1) {
      num % 2 == 0 ? num /= 2 : num *= 3;
      num = ++num / 2;
      std::cout << num << std::endl;
    }
  } else
    std::cout << "Введено некорректное число" << std::endl;

  return 0;
}
