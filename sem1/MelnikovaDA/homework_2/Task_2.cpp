#include <iostream>

void gipSiraquz(int n) {
  while (n != 1) {
    std::cout << n << " ";
    if (n % 2 == 0) {
      n = n / 2;
    } else {
      n = (3 * n + 1) / 2;
    }
  }
  std::cout << 1 << std::endl;
}
int main() {
  int number = 1;
  while (true) {
    std::cout << "Enter a natural number:";
    std::cin >> number;
    if (number <= 0) {
      std::cout << "Error: Enter a natural number." << std::endl;
      number = 1;
    }
    if (number != 1) {
      gipSiraquz(number);
    }
  }
}
