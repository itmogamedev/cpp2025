#include <iostream>

// 1 задача
int main() {
  setlocale(LC_ALL, "Russian");
  std::cout << "Введите сторону квадрата ";
  int side;
  std::cin >> side;
  std::cout << "Его площадь: ";
  std::cout << side * side;
  return 0;
}
