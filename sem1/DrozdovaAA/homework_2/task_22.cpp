#include <iostream>

int syracuseHypothesis(int number);

int main() {
  setlocale(LC_ALL, "Russian");
  int number;
  std::cout << "Число для проверки: ";
  std::cin >> number;
  if (syracuseHypothesis(number)) {
    std::cout << "Получилось 1! ";
  }
  return 0;
}

int syracuseHypothesis(int number) {
  while (number > 1) {
    if (number % 2 != 0) {
      number = number * 3 + 1;
    };
    number /= 2;
  }
  return true;
}
