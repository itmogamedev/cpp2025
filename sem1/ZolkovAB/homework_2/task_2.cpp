#include <iostream>

int main() {
  int num_hex, num_oct;

  std::cout << "Enter num in decimal = ";

  std::cin >> std::hex >> num_hex;

  std::cout << "number is in hexadecimal! " << num_hex;

  std::cout << "Enter num in decimal = ";

  std::cin >> std::oct >> num_oct;

  std::cout << "number is in octdecimal! " << num_oct;
}