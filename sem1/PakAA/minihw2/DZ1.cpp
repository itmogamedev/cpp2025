
#include <iostream>

int main() {
  int number;

  std::cout << "10 number: ";
  std::cin >> number;

  std::cout << "16 number: " << std::hex << number << std::endl;

  std::cout << std::dec;

  std::cout << "8 number: " << std::oct << number << std::endl;

  return 0;
}
// Кондюков топ
