#include <iostream>

int main() {
  int naturalNumber;
  std::cout << "Enter a Natural Number: ";
  std::cin >> naturalNumber;
  if (naturalNumber > 0) {
    while (naturalNumber != 1) {
      if (naturalNumber % 2 == 0) {
        naturalNumber = naturalNumber / 2;
      } else if (naturalNumber % 2 != 0) {
        naturalNumber = (naturalNumber * 3 + 1) / 2;
      }
      std::cout << "Number: " << std::endl;
      std::cout << naturalNumber << std::endl;
      if (naturalNumber == 1) {
        std::cout << "Yes,it works" << std::endl;
      }
    }

  } else {
    std::cout << "You are not write natural number";
  }
  return 0;
}