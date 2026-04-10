// task_2.cpp : вычисляет площадь трапеции
#include <cmath>
#include <iostream>
#include <limits>
#include <locale>
#include <string>
#include <typeinfo>

double trapeciaSquare(double a, double b, double h) {
  double area_square = ((a + b) * h) / 2;
  return area_square;
}

int main() {
  // std::setlocale(LC_CTYPE, "Russian"); // На двух разных компах почему c++
  // работает по разному: один не выводит русский язык с setlocal(), а другой
  // выводит русский только без setlocale()
  double a;
  double b;
  double h;
  std::cout << "Функция подсчёта площади трапеции!\n";
  std::cout << "Введите длину нижней грани трапеции: ";
  std::cin >> a;
  std::cout << "\nВведите длину верхней грани трапеции: ";
  std::cin >> b;
  std::cout << "\nВведите длину высоты трапеции: ";
  std::cin >> h;
  try {
    std::cout << "\nПлощадь трапеции: " << std::to_string(trapeciaSquare(a, b, h)) + "\n";  // to_string переводит переменную double в string тип
  } catch (std::exception ex) {
    std::cout << "Что то пошло не так(!\n" << ex.what();
    return -1;
  }
  return 0;
}
