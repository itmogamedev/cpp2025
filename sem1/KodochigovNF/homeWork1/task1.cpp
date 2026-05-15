#include <iostream>
#include <locale>

double calculateSquareArea(double side_length) {
  return side_length * side_length;
}

int main() {
  setlocale(LC_ALL, "");

  double side_length;
  std::cout << "Введите сторону квадрата: ";
  std::cin >> side_length;

  std::cout << "Площадь квадрата = " << calculateSquareArea(side_length)
            << std::endl;

  return 0;
}
