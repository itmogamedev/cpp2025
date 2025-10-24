#include <bitset>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

// ������� ��� �������������� � ����������������� �������
std::string decimalToHex(int decimal) {
  std::stringstream ss;
  ss << std::hex << decimal;  // ���������� ����������� hex
  return ss.str();
}

// ������� ��� �������������� � ������������ �������
std::string decimalToOctal(int decimal) {
  std::stringstream ss;
  ss << std::oct << decimal;  // ���������� ����������� oct
  return ss.str();
}

int main() {
  int dec;
  std::string oct, hex;
  std::cout << "enter decimal number" << std::endl;
  std::cin >> dec;
  oct = decimalToOctal(dec);
  hex = decimalToHex(dec);
  std::cout << hex << std::endl << oct;
}
