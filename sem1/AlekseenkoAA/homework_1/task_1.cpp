// task_1.cpp : вычисляет площадь квадрата
#include <cmath>
#include <iostream>
#include <limits>
#include <locale>
#include <string>
#include <typeinfo>

double square(double side_lenght) {
  double area_square = std::pow(side_lenght, 2);  // функция pow - возвести в квадрат
  return area_square;
}

int main() {
  // std::setlocale(LC_CTYPE, "Russian"); // На двух разных компах почему c++
  // работает по разному: один не выводит русский язык с setlocal(), а другой
  // выводит русский только без setlocale()
  double a;
  std::cout << "Функция подсчёта площади квадрата!\n";
  std::cout << "Введите длину стороны квадрата: ";
  std::cin >> a;  // получаем длину стороны квадрата
  try {
    std::cout << "\nПлощадь квадрата: " << std::to_string(square(a)) + "\n";  // to_string переводит переменную double в string тип
  } catch (std::exception ex) {
    std::cout << "Что то пошло не так(!\n" << ex.what();
    return -1;
  }
  return 0;
}
