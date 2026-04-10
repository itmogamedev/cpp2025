#include <algorithm>
#include <iostream>
#include <string>

std::string convertFromDecimal(int base, int num) {
  std::string s = "";
  while (num > 0) {
    if (num % base < 10) {
      s += std::to_string(num % base);
    } else {
      s += (char)(55 + num % base);
    }
    num /= base;
  }
  reverse(s.begin(), s.end());
  return s;
}

int main() { return 0; }
