#include <iostream>

int hypothesisTesting(long long int num) {
  while (num > 0) {
    if (num % 2 == 0) {
      num = num / 2;
    } else {
      num = ((num * 3) + 1) / 2;
    }
    if (num == 1) {
      return 1;
    }
  }
  return 0;
}

int main() {
  int num;
  std::cout << "Enter a number to test the Syracuse hypothesis ";
  std::cin >> num;
  if (hypothesisTesting(num) == 1) {
    std::cout << "The hypothesis is correct";
  } else {
    std::cout << "The hypothesis is incorrect";
  }
  return 0;
}
