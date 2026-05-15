#include <iostream>

int main() {
  setlocale(LC_ALL, "Russian");
  int a;

  std::cout << "Введите натуральное число: ";
  std::cin >> a;

  while (a != 1) {
    if (a % 2 == 0) {
      a = a / 2;
    } else {
      a = (a * 3 + 1) / 2;
    }
  }

  if (a == 1) {
    std::cout << "Гипотеза верна, получившееся число: " << a << std::endl;
  } else {
    std::cout << "Гипотеза не верна, получившееся число: " << a << std::endl;
  }

  return 0;
}
