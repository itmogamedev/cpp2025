#include <iostream>

int calculateNextNumber(int number);
bool verificationNaturalness(int number);
void checkTheory(int number);
void printResult(int originalNumber, int steps);

int main() {
  setlocale(LC_ALL, "Russian");
  int number;

  std::cout << "Введите число для проверки теории Сиракуза = ";
  std::cin >> number;

  if (verificationNaturalness(number)) {
    checkTheory(number);
  }

  return 0;
}

bool verificationNaturalness(int number) {
  if (number > 0) {
    return true;
  } else {
    std::cout << "Ошибка. Число должно быть натуральным";
    return false;
  }
}

void checkTheory(int number) {
  int steps = 0;
  int original_number = number;

  std::cout << "Отслеживание изменений: " << number;
  while (number != 1) {
    number = calculateNextNumber(number);
    steps++;
    std::cout << " -> " << number;
  }
  printResult(original_number, steps);
}

void printResult(int original_number, int steps) {
  std::cout << "\n\n_____________Результат_____________" << std::endl;
  std::cout << "Гипотеза Сиракуза подтверждена" << std::endl;
  std::cout << "Исходное число = " << original_number << std::endl;
  std::cout << "Проделанное количество шагов = " << steps << std::endl;
  std::cout << "___________________________________" << std::endl;
}

int calculateNextNumber(int number) {
  return (number % 2 == 0) ? (number / 2) : ((number * 3 + 1) / 2);
}
