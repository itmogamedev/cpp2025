#include <iostream>

void hypothesis(int number) {
  while (number != 1) {
    if (number % 2 == 0) {
      number /= 2;
    } else {
      number = (number * 3 + 1) / 2;
    }
    std::cout << number << "\n";
  }
  std::cout << "Reached 1, hypothesis confirmed!";
}

int main() {
  int number;
  std::cout << "Enter the natural number : ";
  std::cin >> number;
  hypothesis(number);
  return 0;
}
