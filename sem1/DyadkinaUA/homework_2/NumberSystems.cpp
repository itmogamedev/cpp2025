#include <iostream>
#include <string>

std::string ToHex(int number) {
  if (number == 0) return "0";
  char digits[16] = {'0', '1', '2', '3', '4', '5', '6', '7',
                     '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
  std::string hex = "";
  unsigned int n = number;
  while (n > 0) {
    int digit = n % 16;
    hex = digits[digit] + hex;
    n /= 16;
  }
  return hex;
}

std::string ToOctal(int number) {
  if (number == 0) return "0";
  char digits[8] = {'0', '1', '2', '3', '4', '5', '6', '7'};
  std::string octal = "";
  unsigned int n = number;
  while (n > 0) {
    int digit = n % 8;
    octal = digits[digit] + octal;
    n /= 8;
  }
  return octal;
}

int main() {
  int n;
  std::cout << "Введите число: ";
  std::cin >> n;
  std::cout << "Hex: " << ToHex(n) << std::endl;
  std::cout << "Octal: " << ToOctal(n) << std::endl;
  
  return 0;
}
