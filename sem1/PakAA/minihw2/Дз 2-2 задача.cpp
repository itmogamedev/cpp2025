
#include <iostream>

int main() {
  unsigned long long n;

  std::cout << "Enter N: ";
  std::cin >> n;

  std::cout << "Sequence: ";

  while (n != 1) {
    std::cout << n << " ";
    if (n % 2 == 0) {
      n = n / 2;
    } else {
      n = (3 * n + 1) / 2;
    }
  }

  std::cout << n << std::endl;
  std::cout << "Hypothesis correct" << std::endl;

  return 0;
}
