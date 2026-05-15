#include <iostream>

int main() {
  std::cout << "Enter number:\n";

  int num = 0;

  std::cin >> num;

  std::cout << "Number in hexadecimal number system: " << std::hex << num
            << '\n';
  std::cout << "Number in octal number system: " << std::oct << num;

  return 0;
}
