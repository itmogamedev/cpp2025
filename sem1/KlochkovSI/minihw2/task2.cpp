#include <iostream>

int main() {
  long long n;

  std::cout << "Enter a natural: ";
  std::cin >> n;

  if (n <= 0) {
    std::cerr << "Ne natural, menyai" << std::endl;
    return 1;
  }

  int steps = 0;
  std::cout << "Posledovatelnost: " << n;

  while (n != 1) {
    if (n % 2 == 0) {
      n = n / 2;
    } else {
      n = (3 * n + 1);
    }
    std::cout << " -> " << n;
    steps++;
  }

  std::cout << "\nDone for " << steps << " steps" << std::endl;

  return 0;
}
