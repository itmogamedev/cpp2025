#include <iostream>

int main() {
  int number;
  std::cout << "Enter a decimal number: ";
  std::cin >> number;
  std::cout << "Your number in octal system: " << std::oct << number
            << std::endl;
  std::cout << "Your number in a hexadecimal system: " << std::hex << number
            << std::endl;
  return 0;
}