#include <iostream>
#include <string>

std::string syracuseHypothesis(int number) {
  std::string iterations;

  while (number > 1) {
    if (number % 2 == 0) {
      number = number / 2;
    } else {
      number = number * 3 + 1;
    }
    iterations = iterations + std::to_string(number) + " ";
  }

  return iterations;
}

int main() {
  int number;

  std::cout << "Enter a number for Syracuse hypothesis: ";
  std::cin >> number;
  std::cout << syracuseHypothesis(number) << std::endl;

  return 0;
}
