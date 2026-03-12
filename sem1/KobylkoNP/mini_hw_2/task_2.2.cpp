#include <iostream>

int main() {
  int number;
  std::cout << "Enter a natural number: ";
  std::cin >> number;

  int original = number;  // сохраняем исходное число

  if (number <= 0) {
    std::cout << "Error: The number must be a natural number (greater than 0)"
              << std::endl;
    return 1;
  }

  while (number != 1) {
    if (number % 2 == 0) {
      number = number / 2;
    } else {
      number = (number * 3 + 1) / 2;
    }
  }

  std::cout << "The Syracuse conjecture is true for the number: " << original
            << std::endl;

  return 0;
}
