#include <math.h>

#include <iostream>

int main() {
  double num = 0;
  setlocale(LC_ALL, "Russian");
  std::cout << "¬ведите натуральное число:\n";
  std::cin >> num;
  while (num != 1) {
    if (fmod(num, 2) == 0) {
      num /= 2;
    } else
      num = (num * 3 + 1) / 2;
  }
  if (num == 1) {
    std::cout << "√ипотеза верна";
  }
  return 0;
}
