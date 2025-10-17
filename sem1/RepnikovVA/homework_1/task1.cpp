#include <iostream>
#include <string>

float Square(float a) { return a * a; }

int main() {
  setlocale(LC_ALL, "Russian");

  float square_side;
  std::cout << "¬ведите длину стороны квадрата: ";
  std::cin >> square_side;

  float res = Square(square_side);
  std::cout << "ѕлощадь квадрата: " << res << std::endl;

  return 0;
}
