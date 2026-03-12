#include <iostream>

// 2 задача
int main() {
  setlocale(LC_ALL, "Russian");
  std::cout << "Введите первую сторону трапеции ";
  float side_1, side_2, height, answer;
  std::cin >> side_1;
  std::cout << "Введите вторую сторону трапеции ";
  std::cin >> side_2;
  std::cout << "Введите высоту трапеции ";
  std::cin >> height;
  std::cout << "Ee площадь: ";
  answer = ((side_1 + side_2) * height) / 2;
  std::cout << answer;
  return 0;
}
