#include <iostream>
#include <string>

void hexSystem(int number) {
  if (number < 0) {
    std::cout << "Error" << std::endl;
    return;
  } else if (number == 0) {
    std::cout << "0" << std::endl;
    return;
  }

  std::string hex_char = "0123456789ABCDEF";
  std::string result;

  while (number > 0) {
    int prom_var = number % 16;
    result = hex_char[prom_var] + result;
    number = number / 16;
  }

  std::cout << result << std::endl;
}

void octSystem(int number) {
  if (number < 0) {
    std::cout << "Error" << std::endl;
    return;
  } else if (number == 0) {
    std::cout << "0" << std::endl;
    return;
  }

  std::string hex_char = "01234567";
  std::string result;

  while (number > 0) {
    int prom_var = number % 8;
    result = hex_char[prom_var] + result;
    number = number / 8;
  }

  std::cout << result << std::endl;
}

int main() {
  int num = 0;
  std::cout << "Enter number:";
  std::cin >> num;

  std::cout << "-----------------------------" << std::endl;
  std::cout << "Hex system number:";
  hexSystem(num);

  std::cout << "Oct system number:";
  octSystem(num);
}
