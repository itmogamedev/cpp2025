#include <iostream>

int main() {
  int n;
  std::cout << "write a number" << std::endl;
  std::cin >> n;
  std::cout << "octal number system: " << std::oct << n << std::endl;
  std::cout << "hexadecimal number system: " << std::hex << n << std::endl;

  return 0;
}
