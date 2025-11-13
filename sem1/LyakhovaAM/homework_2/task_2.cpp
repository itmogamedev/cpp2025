#include <iostream>

int main() {
  int number;
  std::cout << "Please, give me a number: ";
  std::cin >> number;
  std::cout << '\n';
  while (number != 1) {
    if (number % 2)
      number = (number * 3 + 1) / 2;
    else
      number /= 2;
  }
  if (number == 1)
    std::cout << "I Agree With That!";
  else
    std::cout << "No, That's Wrong!";
  return 0;
}
