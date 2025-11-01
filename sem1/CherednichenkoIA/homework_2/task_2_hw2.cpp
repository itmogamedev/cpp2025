#include <iostream>
int main() {
  unsigned long long n;
  std::cout << "n = ";
  std::cin >> n;
  while (n != 1) {
    std::cout << n << ' ';
    n = (n & 1) ? (3 * n + 1) / 2 : n / 2;
    if (n == 1) {
      std::cout << n << " ";
    }
  }
  std::cout << std::endl << "Agree";
}
