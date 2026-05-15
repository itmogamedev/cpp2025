#include <iostream>

int main() {
  int number;
  std::cout << "Enter any natural number: ";
  std::cin >> number;

  while (number != 1) {
    if (number % 2 == 0) {
      number /= 2;
      std::cout << number << " ";
    } else {
      number = (number * 3 + 1) / 2;
      std::cout << number << " ";
    }
  }
  std::cout << "\n";
  std::cout << "Syracuse's hypothesis is correct";
}
