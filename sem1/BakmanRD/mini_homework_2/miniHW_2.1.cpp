#include <iostream>

int main() {
  int number;
  std::cout << "please enter a number: ";
  std::cin >> number;
  std::cout << "the hexadecimal form of the number is " << std::hex << number
            << std::endl;
  std::cout << "the octal form of the number is " << std::oct << number;

  return 0;
}
