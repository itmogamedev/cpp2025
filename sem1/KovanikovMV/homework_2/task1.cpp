#include <iostream>
#include <string>

std::string intToHex(int x) {
  std::string buffer = "";
  std::string alphabet = "0123456789abcdef";
  std::string hex = "0x";
  if (x == 0) {
    return "0x0";
  }
  while (x != 0) {
    buffer += alphabet[x % 16];
    // я пока не знаю, как создавать массив с динамичным выделением памяти,
    // поэтому пока что просто перезаписываю string каждый раз
    x /= 16;
  }
  for (int i = buffer.length(); i >= 0; i--) {
    hex += buffer[i];
  }
  return hex;
}

std::string intToOct(int x) {
  std::string buffer = "";
  std::string alphabet = "01234567";
  std::string oct = "0o";
  if (x == 0) {
    return "0o0";
  }
  while (x != 0) {
    buffer += alphabet[x % 8];
    x /= 8;
  }
  for (int i = buffer.length(); i >= 0; i--) {
    oct += buffer[i];
  }
  return oct;
}

int main() {
  std::cout << "Input your integer" << std::endl;
  int integer;
  std::cin >> integer;
  std::cout << "Your hexadecimal is " << intToHex(integer) << std::endl;
  std::cout << "Your octal is " << intToOct(integer) << std::endl;
}
