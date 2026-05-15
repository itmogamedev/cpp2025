#include <iostream>

int main() {
  int number;
  std::cout << "Enter a number: ";
  std::cin >> number;
  std::cout << "Number in hex: " << std::hex << number << std::endl;
  std::cout << "Number in oct: " << std::oct << number << std::endl;
}
