#include <iostream>

int main() {
  setlocale(LC_ALL, "Russian");
  int a;

  std::cout << "������� ����������� �����: ";
  std::cin >> a;

  while (a != 1) {
    if (a % 2 == 0) {
      a = a / 2;
    } else {
      a = (a * 3 + 1) / 2;
    }
  }

  if (a == 1) {
    std::cout << "�������� �����, ������������ �����: " << a << std::endl;
  } else {
    std::cout << "�������� �� �����, ������������ �����: " << a << std::endl;
  }

  return 0;
}
