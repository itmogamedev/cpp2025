#include <iostream>

void thr(int x) {
  int step = 0;

  if (x < 1) {
    std::cout << "Введено не натуральное число\n";
    return;
  }

  for (step; x != 1; step++) {
    bool evenness = (x % 2) == 0;

    if (evenness) {
      x = x / 2;
    }

    else {
      x = (3 * x + 1) / 2;
    }

    std::cout << x << std::endl;
  }
  std::cout << "Выполнено за " << step << " шагов" << std::endl;
}

int main() {
  system("chcp 1251 > nul");
  int number = 0;

  while (true) {
    std::cout << "Ведите число для проверки гипотезы Сиракуз: ";
    std::cin >> number;
    thr(number);
  }
}
