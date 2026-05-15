#include <iostream>

int main() {
  int number;
  
  std::cout << "Enter a natural number: ";
  std::cin >> number;
  
  if (number <= 0) {
    std::cout << "Error! Please enter a natural number (greater than 0)." << std::endl;
    return 1;
  }
  
  std::cout << "Sequence of numbers:" << std::endl;
  
  while (number != 1) {
    std::cout << number << " ";
    
    if (number % 2 == 0) {
      number = number / 2;
    } else {
      number = (number * 3 + 1) / 2;
    }
  }
  
  std::cout << number << std::endl;
  
  return 0;
}