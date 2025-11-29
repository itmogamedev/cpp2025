#include <iostream>

void SyracuseHypothesis(int n) {
  std::cout << "Последовательность для числа " << n << ": " << n << " ";

  while (n != 1) {
    if (n % 2 == 0) {
      n = n / 2;
    } else {
      n = (3 * n + 1) / 2;
    }
    std::cout << n << " ";
  }

  std::cout << std::endl;
}

int main() {
  int number;
  setlocale(LC_ALL, "Russian");
  std::cout << "Введите натуральное число: ";
  std::cin >> number;

  if (number <= 0) {
    std::cout << "Введите натуральное число больше 0." << std::endl;
    return 1;
  }

  SyracuseHypothesis(number);

  return 0;
}
