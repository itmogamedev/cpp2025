#include <iostream>

void convert(int a) {
  std::cout << "hex: " << std::hex << a;
  std::cout << "\noct: " << std::oct << a;
}

int main() {
  int a = 0;
  std::cout << "Enter number: ";
  std::cin >> a;
  convert(a);
}
