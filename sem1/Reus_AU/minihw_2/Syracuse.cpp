#include <iostream>

void syracuseHypothesis(unsigned long long num) {
  while (num != 1) {
    std::cout << num << " ";
    if (num % 2 == 0) {
      num = num / 2;
    }
    else {
      num = (3 * num + 1) / 2;
    }
    }
    std::cout << num << std::endl;
}

int main() {
  unsigned long long num;
  std::cout << "Enter number: ";
  std::cin >> num;
  syracuseHypothesis(num);
  return 0;
}
