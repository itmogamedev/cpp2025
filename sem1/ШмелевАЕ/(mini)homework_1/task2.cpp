#include <iostream>
double sTrapezii(double side_a, double side_b, double side_h) {
  return (side_a + side_b) / 2 * side_h;
}
int main() {
  setlocale(LC_ALL, "RU");
  double side_a, side_b, side_h;
  std::cout << "��������� a = ";
  std::cin >> side_a;
  std::cout << "��������� b = ";
  std::cin >> side_b;
  std::cout << "������ h = ";
  std::cin >> side_h;
  std::cout << "S �������� = " << sTrapezii(side_a, side_b, side_h);
  return 0;
}
