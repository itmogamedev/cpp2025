#include <iostream>

int main() {
  long long n;
  std::cout << "Enter a positive integer: ";
  std::cin >> n;

  if (n <= 0) {
    std::cout << "Please enter a positive integer." << std::endl;
    return 1;
  }

  while (n != 1) {
    if (n % 2 == 0) {
      n = n / 2;
    } else {
      n = 3 * n + 1;
    }
    std::cout << n << " " << n;
  }
  std::cout << std::endl;
  return 0;
}
