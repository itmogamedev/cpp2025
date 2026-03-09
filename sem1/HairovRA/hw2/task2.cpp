#include <iostream>

int main() {
  int n;

  std::cout << "write number" << std::endl;
  std::cin >> n;
  while (n > 1) {
    if (n % 2 == 0) {
      n = n / 2;

    } else {
      n = (n * 3 + 1) / 2;
    }
    std::cout << n << std::endl;
  }
  std::cout << "we did it!";
}
