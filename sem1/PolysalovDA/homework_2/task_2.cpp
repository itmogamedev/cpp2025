#include <iostream>
#include <string>

bool IsNatural(int number) {
  if (number != 0 && number > 0) {
    return true;
  } else {
    return false;
  }
}

int HypSirakuz(int number) {
  if (number == 1) {
    return 1;
  }
  if (!(number % 2)) {
    number /= 2;
  } else {
    number = ((number * 3) + 1) / 2;
  }

  return HypSirakuz(number);
}

int main() {
  int entered_number;
  while (true) {
    std::cout << "Введите натуральное число: ";
    std::cin >> entered_number;
    if (IsNatural(entered_number)) {
      if (bool(HypSirakuz(entered_number))) {
        std::cout << HypSirakuz(entered_number) << std::endl;
        std::cout << "Гипотеза Доказана!" << std::endl;
      } else {
        std::cout << "Получается не работает гипотеза";
      }
      continue;
    }
  }
}