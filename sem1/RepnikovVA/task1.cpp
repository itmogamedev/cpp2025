#include <iostream>

float Square(float side) { return side * side; }

int main() {
  setlocale(LC_ALL, "Russian");

  float side;
  std::cout << "¬ведите длину стороны квадрата: ";
  std::cin >> side;

  float result = Square(side);
  std::cout << "ѕлощадь квадрата: " << result;
}
