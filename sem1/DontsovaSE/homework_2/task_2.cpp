#include <iostream>
#include <limits>

int main() {
  long long temp;
  std::cout << "Введите натуральное число: ";

  while (!(std::cin >> temp) || temp <= 0) {
    std::cout << "Ошибка: введите корректное натуральное число (> 0): ";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  unsigned long long n = static_cast<unsigned long long>(temp);
  unsigned long long steps = 0;
  std::cout << "Последовательность:\n" << n;

  while (n != 1) {
    if (n % 2 == 0) {
      n /= 2;
    } else {
      if (n > (std::numeric_limits<unsigned long long>::max() - 1) / 3) {
        std::cerr
            << "\nОшибка: переполнение при вычислении 3*n + 1. Прекращаем.\n";
        return 1;
      }
      n = (3 * n + 1) / 2;
    }
    std::cout << " -> " << n;
    ++steps;

    if (steps > 10000000) {
      std::cout
          << "\nСлишком много шагов (>10 000 000). Прекращаем проверку.\n";
      return 1;
    }
  }

  std::cout << "\nДостигнута 1 за " << steps << " шагов.\n";
  return 0;
}
