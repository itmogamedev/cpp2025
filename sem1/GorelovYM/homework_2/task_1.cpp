#include <iostream>
#include <string>

std::string toBase(int number, int base) {
  std::string str = "";
  while (number >= base) {
    str = (char)(number % base + '0') + str;
    number /= base;
  }
  str = (char)(number % base + '0') + str;
  return str;
}

int main(void) {
  int number;
  std::cin >> number;
  std::cout << "0x" << toBase(number, 16) << "; 0o" << toBase(number, 8);
}
