#include <iostream>
double squareArea(double side) { return side * side; }
int main() {
  setlocale(LC_ALL, "RU");
  std::cout << "������� ������ �������: ";
  double side_size;
  std::cin >> side_size;
  std::cout << "S = " << squareArea(side_size);
  return 0;
}
