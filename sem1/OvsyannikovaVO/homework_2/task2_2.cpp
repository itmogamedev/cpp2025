#include <iostream>

bool syrakys(int num) {
  while (num != 1) {
    if (num % 2 == 0) {
      num /= 2;
    } else {
      (num = num * 3 + 1) / 2;
    }
  }
  if (num == 1) {
    return true;
  }
}

int main() {
  std::cout << "This program tests the Syracuse hypothesis\n";
  std::cout << "Enter your number:\n";
  int numb;
  std::cin >> numb;
  if (syrakys(numb) == 1) {
    std::cout << "Hypothesis is correct! You got 1";
  } else {
    std::cout << "Hypothesis is wrong :(";
  }

  return 0;
}
