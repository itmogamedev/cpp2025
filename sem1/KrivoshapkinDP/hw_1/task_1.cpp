#include <iostream>

double square(double a) { return a * a; }

int main() {
  setlocale(LC_ALL, "Russian");
  double a;
  std::cout << "������� ����� ������� ��������(a): ";
  std::cin >> a;

  double s = square(a);
  std::cout << "������� ��������: " << s << std::endl;

  return 0;
}
