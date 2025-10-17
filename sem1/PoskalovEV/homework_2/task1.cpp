#include <string>

const static std::string alphabet = "0123456789abcdefghijklmnopqrstuvwxyz";

std::string decimalToBase(int number, unsigned int base) {
  if (base >= alphabet.length()) return "";

  std::string result = "";

  if (number < 0) {
    result += '-';
  }

  while (number > 0) {
    result += alphabet[number % base];
    number /= base;
  }

  for (std::size_t i = 0; i < result.size() / 2; i++) {
    std::swap(result[i], result[result.size() - i - 1]);
  }
  return result;
}

std::string toHex(int number) { return decimalToBase(number, 16); }

std::string toOct(int number) { return decimalToBase(number, 8); }

#include <iostream>

int main() {
  std::cout << "752 to base 8: " << toOct(752) << std::endl;
  std::cout << "752 to base 16: " << toHex(752) << std::endl;

  return 0;
}