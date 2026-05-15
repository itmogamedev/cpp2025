#include <algorithm>
#include <iostream>
#include <string>

std::string DecToHex(int a) {
  if (a == 0) {
    return "0";
  }

  std::string hex_chars = "0123456789ABCDEF";
  std::string hex_result = "";

  while (a > 0) {
    int ostatok = a % 16;
    hex_result += hex_chars[ostatok];
    a /= 16;
  }

  std::reverse(hex_result.begin(), hex_result.end());

  return hex_result;
}

std::string DecToOct(int b) {
  if (b == 0) {
    return "0";
  }

  std::string oct_chars = "01234567";
  std::string oct_result = "";

  while (b > 0) {
    int ost = b % 8;
    oct_result += oct_chars[ost];
    b /= 8;
  }

  std::reverse(oct_result.begin(), oct_result.end());

  return oct_result;
}

int main() {
  int DecNumb = 0;
  std::cout << "Enter a number: ";
  std::cin >> DecNumb;
  std::string hex_string = DecToHex(DecNumb);
  std::string oct_string = DecToOct(DecNumb);
  std::cout << "OCT: " << oct_string << std::endl;
  std::cout << "HEX: " << hex_string << std::endl;

  return 0;
}
