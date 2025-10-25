#include <iostream>

std::string convertation(int num, int sy) {
  const std::string alphabet = "0123456789ABCDEFGHI";
  std::string result = "";
  bool is_negative = num < 0;

  if (num == 0) {
    return "0";
  }

  if (is_negative) {
    num = num * -1;
  }

  if (num > 0) {
    while (num > 0) {
      result = alphabet[num % sy] + result;
      num /= sy;
    }

    if (is_negative) {
      result = '-' + result;
    }
    return result;
  }
}

int main() {
  system("chcp 1251 > nul");

  int number = 0;
  while (true) {
    std::cout << "������ �����: ";
    std::cin >> number;

    std::cout << "����� � 8 ������� ���������� " << convertation(number, 8)
              << std::endl;
    std::cout << "����� � 16 ������� ���������� " << convertation(number, 16)
              << std::endl;
  }
}
