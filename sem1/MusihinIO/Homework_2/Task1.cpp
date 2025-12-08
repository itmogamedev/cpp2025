#include <iostream>
#include <string>

std::string decToOct(int number) {
  std::string oct_result;
  for (; number; number /= 8) {
    oct_result = char('0' + number % 8) + oct_result;
  }

  return oct_result.empty() ? "0" : oct_result;
}

std::string decToHex(int number) {
  const std::string kHexChars = "0123456789ABCDEF";
  std::string hex_result;

  while (number > 0) {
    hex_result = kHexChars[number % 16] + hex_result;
    number /= 16;
  }

  return hex_result.empty() ? "0" : hex_result;
}

int main() {
  int number;

  std::cout << "Enter a number to convert it from Dec to Oct: ";
  std::cin >> number;
  std::cout << number << " -> " << decToOct(number) << std::endl;

  std::cout << "Enter a number to convert it from Dec to Hex: ";
  std::cin >> number;
  std::cout << number << " -> " << decToHex(number) << std::endl;

  return 0;
}
