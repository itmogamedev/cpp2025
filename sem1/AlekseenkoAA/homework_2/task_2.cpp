// task_2.cpp : проверяет гипотезу Сиракуз
#include <iostream>
#include <limits>
#include <string>

int main() {
  // std::setlocale(LC_CTYPE, "Russian"); // На двух разных компах почему c++
  // работает по разному: один не выводит русский язык с setlocal(), а другой
  // выводит русский только без setlocale()
  /* Программа Сиракуз */
  std::cout << "Программа, которая проверяет гипотезу Сиракуз \n";
  unsigned long long sample_b;
  unsigned long long operations_count = 0;
  std::cout << "Введите любое натуральное число: ";
  std::cin >> sample_b;
  while (true) {
    if (sample_b == 1) {
      break;
    } else if (sample_b % 2 == 0) {
      sample_b /= 2;
    } else {
      sample_b *= 3;
      sample_b += 1;
      sample_b /= 2;
    }
    operations_count += 1;
  }
  std::cout << "Полученное число после преобрезований: " << sample_b << "\n" << "Затраченно операций цикла: " << operations_count << "\n";
  if (sample_b == 1ULL) {
    std::cout << "Теория Сиракуза верна";
  } else {
    std::cout << "Теория Сиракуза НЕ верна";
  }
  return 0;
}
