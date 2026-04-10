#include <iostream>
#include <locale>

void checkSyracuseHypothesis(int number) {
  std::cout << "Начальное число: " << number << std::endl;

  while (number != 1) {
    if (number % 2 == 0) {
      number /= 2;
    } else {
      number = (3 * number + 1) / 2;
    }

    std::cout << number << " ";
  }

  std::cout << std::endl << "Гипотеза подтверждена: достигнуто 1." << std::endl;
}

int main() {
  setlocale(LC_ALL, "");

  int user_number;
  std::cout << "Введите натуральное число: ";
  std::cin >> user_number;

  if (user_number <= 0) {
    std::cout << "Ошибка: нужно ввести натуральное число (> 0)." << std::endl;
    return 0;
  }

  checkSyracuseHypothesis(user_number);

  return 0;
}
