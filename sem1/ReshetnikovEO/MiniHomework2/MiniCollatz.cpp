#include <iostream>

int collatz(int numb) {
  if (numb == 1) return 1;
  if (numb % 2 == 0)
    return collatz(numb / 2);
  else
    return collatz(((numb * 3) + 1) / 2);
}

int main() {
  int numb;
  std::cout << "Type the number you want to check for Collatz conjecture" << std::endl;
  while (true) {
    std::cin >> numb;
    if (numb > 0) break;
    std::cout << "Please type something more then 0" << std::endl;
  }

  std::cout << "Your number = " << collatz(numb) << std::endl;
  return 0;
}
