#include <iostream>

int main() {
  int num;

  std::cout << "Enter a number: ";
  std::cin >> num;

  while (num != 1) {
    if (num % 2 == 0)
      num /= 2;
    else
      num = ((num * 3) + 1) / 2;
    std::cout << "Num is " << num << std::endl;
  }
  return 0;
}
