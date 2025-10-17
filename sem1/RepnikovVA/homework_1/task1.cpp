#include <iostream>
#include <string>

float Square(float square_side) { return square_side * square_side; }

int main() {
  setlocale(LC_ALL, "Russian");

  float square_side;
  std::cout << "¬ведите длину стороны квадрата: ";
  std::cin >> square_side;

  float result = Square(square_side);
  std::cout << "ѕлощадь квадрата: " << result << std::endl;

  return 0;
}
