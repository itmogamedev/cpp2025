#include <iostream>
int main() {
  int number;

  std::cout << "enter a natural number to test the Syracuse hypothesis: ";
  std::cin >> number;

  if (number == 0) {
    std::cout << "error! enter a natural number!" << std::endl;
    return 1;
  }

  int steps = 0;
  while (number > 1) {
    std::cout << number << " ";

    if (number % 2 == 0) {
      number = number / 2;
    } else {
      number = (number * 3 + 1) / 2;
    }
    steps++;
  }

  std::cout << "1" << std::endl;
  std::cout << "steps: " << steps;
  return 0;
}