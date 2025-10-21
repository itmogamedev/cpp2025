#include <clocale>
#include <iostream>

int main() {
  setlocale(LC_ALL, "Russian");

  int nat_num = 0;

  std::cout << "Введите натуральное число: ";
  std::cin >> nat_num;

  std::cout << "Промежуточные результаты проверки: " << std::endl;

  while (nat_num != 1) {
    if (nat_num % 2 == 0) {
      nat_num = nat_num / 2;
      std::cout << nat_num << std::endl;
    } else {
      nat_num = ((nat_num * 3) + 1) / 2;
      std::cout << nat_num << std::endl;
    }
  }

  std::cout << "Алгоритм проверки гипотизы Сиракуза вернул: " << nat_num;
}
