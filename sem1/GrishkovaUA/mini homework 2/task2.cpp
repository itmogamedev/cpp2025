#include <iostream>

int main() {
  unsigned int natural_number;
  std::cout << "Enter a natural number: ";
  std::cin >> natural_number;

  std::cout << natural_number << " ";
  while (natural_number != 1) {
    if (natural_number % 2 == 0) {
      natural_number /= 2;
    } else {
      natural_number = (3 * natural_number + 1) / 2;
    }
    std::cout << natural_number << " ";
  }
  std::cout << std::endl;
  return 0;
}
