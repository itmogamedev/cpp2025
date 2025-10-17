#include <iostream>

std::string convert(int n, int x) {
  std::string digits = "0123456789ABCDEF";
  std::string result = "";

  if (n == 0) return 0;

  while (n > 0) {
    int ostatok = n % x;
    result = digits[ostatok] + result;
    n /= x;
  }
  return result;
}

int main() {
  system("chcp 1251");
  system("cls");

  int nums = 0;

  std::cout << "Введите число: ";
  std::cin >> nums;

  std::cout << "В восьмеричной системе: " << convert(nums, 8) << std::endl;
  std::cout << "В шестнадцатеричной системе: " << convert(nums, 16) << std::endl;

  return 0;
}