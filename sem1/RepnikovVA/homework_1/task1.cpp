#include <iostream>
#include <string>

float Square(float a) { return a * a; }

int main() {
  setlocale(LC_ALL, "Russian");

  float square_side;
  std::cout << "������� ����� ������� ��������: ";
  std::cin >> square_side;

  float res = Square(square_side);
  std::cout << "������� ��������: " << res << std::endl;

  return 0;
}
