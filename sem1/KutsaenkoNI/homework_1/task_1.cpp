#include <iostream>

double square_area(double side) { return side * side; }

int main() {
  double side;
  setlocale(LC_ALL, "Russian");
  std::cout << "Введите сторону квадрата: " << std::endl;
  std::cin >> side;
  if (side <= 0) {
    std::cout << "Сторона квадрата не может быть отрицательной";
    return 1;
  }

  std::cout << "Площадь квадрата: " << square_area(side) << std::endl;
  return 0;
}
