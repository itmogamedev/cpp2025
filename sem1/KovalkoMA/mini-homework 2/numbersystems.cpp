#include <iostream>
#include <sstream>

std::string decimal_to_hex(int decimal) {
  std::ostringstream ss;
  ss << std::hex << decimal;
  return ss.str();
}

std::string decimal_to_oct(int decimal) {
  std::ostringstream ss;
  ss << std::oct << decimal;
  return ss.str();
}

int main() {
  int n;
  std::cout << "Enter your decimal value: ";
  std::cin >> n;

  std::string hex_str = decimal_to_hex(n);
  std::cout << "Hexadecimal value = " << hex_str << std::endl;

  std::string oct_str = decimal_to_oct(n);
  std::cout << "Octal value = " << oct_str << std::endl;

  return 0;
}
