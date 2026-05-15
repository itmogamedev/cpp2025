#include <iostream>

int main() {
  std::cout << "Enter natural number:\n";

  int n = 0;

  std::cin >> n;

  while (true) {
    if (n == 1) {
      std::cout << "The hypothesis is true";
      break;
    }

    if (n % 2 == 0) {
      n /= 2;
    } else {
      n = ((n * 3) + 1) / 2;
    }
  }
}