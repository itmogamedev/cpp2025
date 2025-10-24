int syracuse(long long number) {
  while (number != 1) {
    if (number % 2 == 1) {
      number *= 3;
      number += 1;
    }
    number /= 2;
  }

  return 1;
}

#include <iostream>

int main() {
  for (int i = 1; i < 10000000; i++) {
    syracuse(i);
  }

  std::cout << "problem solved" << std::endl;
  return 0;
}