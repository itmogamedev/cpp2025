#include <iostream>

int main() {
  long int n;
  std::cout << "write a number: " << std::endl;
  std::cin >> n;

  if (n > 0) {
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
    std::cout << "Hypothesis is correct" << std::endl;

  } else {
    std::cout << "try a number > 0" << std::endl;
  }

  return 0;
}
