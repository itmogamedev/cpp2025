#include <iostream>

float Square(float side) { return side * side; }

int main() {
  setlocale(LC_ALL, "Russian");

  float side;
  std::cout << "������� ����� ������� ��������: ";
  std::cin >> side;

  float result = Square(side);
  std::cout << "������� ��������: " << result;
}
