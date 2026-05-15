#include <algorithm>
#include <iostream>

long long oct(long long number) {
  long long oct_number = 0;
  for (long long power = 1; number; power *= 10) {
    oct_number += number % 8 * power;
    number /= 8;
  }
  return oct_number;
}

std::string hex(long long number) {
  std::string hex_number = "";
  while (number) {
    if (number % 16 < 10)
      hex_number += char(number % 16 + '0');
    else
      hex_number += char(number % 16 - 10 + 'A');
    number /= 16;
  }
  std::reverse(hex_number.begin(), hex_number.end());
  return hex_number;
}

int main() {
  long long number;
  std::cout << "Please, give me a number: ";
  std::cin >> number;
  std::cout << '\n'
            << "The oct: " << oct(number) << '\n'
            << "The hex: " << hex(number);
  return 0;
}
