#include <iostream>

int main() {
  setlocale(LC_ALL, "Russian");
  int a;

  std::cout << "������� ���������� �����: ";
  std::cin >> a;

  std::cout << "����������������� �����: " << std::hex << a << std::endl;
  std::cout << "������������ �����: " << std::oct << a << std::endl;

  return 0;
}
