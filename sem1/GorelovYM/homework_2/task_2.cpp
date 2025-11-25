#include <iostream>
#include <string>

int main(void) {
  int random, steps = 0;
  std::cout << "Enter any number: ";
  std::cin >> random;

  while (random > 1) {
    if (random % 2 == 0)
      random /= 2;
    else
      random = (random * 3 + 1) / 2;
    steps++;
  }
  std::cout << "Ended in " << steps << " steps";
}
