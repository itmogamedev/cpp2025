#include <iostream>
#include <string>

float Square(float square_side) { return square_side * square_side; }

int main() {
  setlocale(LC_ALL, "Russian");

  float square_side;
  std::cout << "������� ����� ������� ��������: ";
  std::cin >> square_side;

  float result = Square(square_side);
  std::cout << "������� ��������: " << result << std::endl;

  return 0;
}
