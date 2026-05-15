#include <string>
#include <format>

///<summary>Converts the specified number to hexadecimal system</summary>
std::string convertToHex(int number) {
  return std::format("{:X}", number);
}

///<summary>Converts the specified number to octal system</summary>
std::string convertToOctal(int number) {
  return std::format("{:o}", number);
}

// Sample usage
#include <cassert>
#include <iostream>

int main() {
  assert((convertToHex(79) == "4F"));

  int num;
  std::cout << "Enter the number you want to convert: ";
  std::cin >> num;
  std::cout << std::format("Number {} in hexadecimal is 0x{}, and in octal is 0o{}", num, convertToHex(num),
                           convertToOctal(num));
}
