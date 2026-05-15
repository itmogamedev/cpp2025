#include <iostream>
#include <string>

int main() {
  int number;
  std::cout << "Enter number: ";
  std::cin >> number;

  // ѕреобразование в восьмеричную систему
  int temp = number;
  std::string octal = "";

  if (temp == 0) {
    octal = "0";
  } else {
    while (temp > 0) {
      octal = std::to_string(temp % 8) + octal;
      temp = temp / 8;
    }
  }

  // ѕреобразование в шестнадцатеричную систему
  temp = number;
  std::string hex = "";
  std::string digits = "0123456789ABCDEF";

  if (temp == 0) {
    hex = "0";
  } else {
    while (temp > 0) {
      hex = digits[temp % 16] + hex;
      temp = temp / 16;
    }
  }

  std::cout << "Octal: " << octal << std::endl;
  std::cout << "Hexadecimal: " << hex << std::endl;

  return 0;
}
