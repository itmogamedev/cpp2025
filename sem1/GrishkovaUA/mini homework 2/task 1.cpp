#include <iostream>
#include <string>

std::string intToHex(int value) {
  if (value == 0) return "0";
  std::string hex_digits = "0123456789ABCDEF";
  std::string result;
  unsigned int n = value;
  while (n > 0) {
    int digit = n % 16;
    result = hex_digits[digit] + result;
    n /= 16;
  }
  return result;
}

int main() {
  int number;
  std::cout << "Enter number: ";
  std::cin >> number;
  std::cout << "Hex number: " << intToHex(number) << std::endl;
  return 0;
}
