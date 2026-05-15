#include <iostream>

int main() {
  system("chcp 1251");
  system("cls");

  int n = 0;
  int x = 1;

  std::cout << "Введите натуральное число (>1): " << std::endl;
  std::cin >> n;

  if (n < 0 || n == 0) {
    std::cout << "Ошибка: введите положительное целое число.";
    return 0;
  } else if (n == 1){
    std::cout << "Суть гипотезы Сиракуз в том, что в итоге всегда получается 1.";
  }
    
  std::cout << "Последовательность:" << std::endl;

  while (n != 1) {
    if (n % 2 == 0) {
      n /= 2;
    }
    else
    {
        n = (n * 3 + 1) / 2;
    }
    std::cout << x << " - " << n << std::endl;
    x++;
  }
  std::cout << "Гипотеза подтверждена";
  return 0;
}