#include <iostream>

int octNumber(int number) {
  std::cout.unsetf(std::ios::dec);
  std::cout.setf(std::ios::oct);
  return number;
}
int hexNumber(int number) {
  std::cout.unsetf(std::ios::dec);
  std::cout.setf(std::ios::hex);
  return number;
}
int main() {
  setlocale(LC_ALL, "rus");
  int dec_number;
  int measuring_system;
  std::cout << "������ ����� � ���������� ������� ���������: ";
  std::cin >> dec_number;
  std::cout << "�������, � ����� ������� ��������� ��������� ����� (8/16): ";
  std::cin >> measuring_system;
  if (measuring_system == 8) {
    std::cout << "���� �����: " << octNumber(dec_number);
  } else if (measuring_system == 16) {
    std::cout << "���� �����: " << hexNumber(dec_number);
  } else {
    std::cout << "��������� ��������� ������ � ������������ � "
                 "����������������� �������.";
  }
  return 0;
}
