#include <iostream>

int main() {
  int nat = 0;

  std::cout << "Начальное натуральное число: ";
  std::cin >> nat;
  
  std::cout << "Маршрут: ";
  while (nat != 1) {
    std::cout << nat << " ";
    if (nat % 2 == 0) {
      nat /= 2;
    }
    else {
      nat = (3 * nat + 1) / 2;
    }
  }
  std::cout << std::endl;

  std::cout << "Итог: 1, гипотеза верна :D" << std::endl;

  return 0;
}

