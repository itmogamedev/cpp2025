#include <iostream>
#include <string>

std::string toBase(int num, int base) {
  std::string digits = "0123456789ABCDEF";
  std::string result = "";
  if (num == 0) return "0";
  while (num > 0) {
    int remainder = num % base;
    result = digits[remainder] + result;
    num /= base;
  }
  return result;
}

int main() {
  int number;
  std::cout << "Your number: ";
  std::cin >> number;
  std::cout << "Oct base: " << toBase(number, 8) << std::endl;
  std::cout << "Hex base: " << toBase(number, 16) << std::endl;
  return 0;
}