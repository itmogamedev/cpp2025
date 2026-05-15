#include <iostream>

int main() {
  float side_length;

  setlocale(LC_ALL, "Rus");
  std::cout << "Введите сторону квадрата: ";
  std::cin >> side_length;
  if (side_length > 0) {
    std::cout << "Площадь квадрата равна: ";
    std::cout << side_length * side_length;
  } else {
    std::cout << "Невозможная сторона квадрата";
  }
}
