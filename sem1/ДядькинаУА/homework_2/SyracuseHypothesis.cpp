#include <iostream>

void SyracuseHypothesis(int number) {
  std::cout << number;
  while (number != 1) {
    if (number % 2 == 0) {
      number = number / 2;
    } else {
      number = (3 * number + 1) / 2;
    }
    std::cout << " " << number;
  }
  std::cout << std::endl;
}

int main() {
  int input_number;
  std::cout << "Введите натуральное число: ";
  std::cin >> input_number;
  if (input_number == 0) {
    std::cout << "Число должно быть натуральным." << std::endl;
    return 1;
  }
  SyracuseHypothesis(input_number);
  
  return 0;
}