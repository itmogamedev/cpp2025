
// Минидомашка 2
// Задача 2: Реализовать программу, которая проверяет гипотезу Сиракуз.

#include <iostream>
int hypothesisTest(int step_number) {
  if (step_number == 1) {
    return (1);
  } else if (step_number % 2 == 0) {
    return (step_number / 2);
  } else {
    return ((step_number * 3 + 1) / 2);
  }
}

int main() {
  int entered_number;
  std::cout << "Please, enter the number: ";
  while (true) {
    std::cin >> entered_number;
    if (hypothesisTest(entered_number)) {
      std::cout << "The hypothesis works on the number " << entered_number
                << std::endl;
    } else {
      std::cout << "The hypothesis does not work on the number "
                << entered_number << std::endl;
    }
    std::cout << "\nPlease, enter a new number: ";
  }
}
