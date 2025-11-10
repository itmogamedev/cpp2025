#include <iostream>
#include <string>

int main() {
  int number;
  std::cout << "Chislo:";
  std::cin >> number;

  std::cout << "Vosmerichnoe:";
  int temp = number;

  if (temp == 0) {
    std::cout << "0";
  } else if (temp > 0) {
    std::string octal = "";
    while (temp > 0) {
      int ostatok = temp % 8;
      octal = std::to_string(ostatok) + octal;
      temp = temp / 8;
    }
    std::cout << octal;
  } else {
    temp = -temp;
    std::string octal = "";
    while (temp > 0) {
      int ostatok = temp % 8;
      octal = std::to_string(ostatok) + octal;
      temp = temp / 8;
    }
    std::cout << "-" << octal;
  }

  std::cout << std::endl;

  std::cout << "Shestnatherichnoe:";
  temp = number;

  if (temp == 0) {
    std::cout << "0";
  } else if (temp > 0) {
    std::string hex = "";
    while (temp > 0) {
      int ostatok = temp % 16;
      char hexChar;
      if (ostatok < 10) {
        hexChar = '0' + ostatok;
      } else {
        hexChar = 'A' + (ostatok - 10);
      }
      hex = hexChar + hex;
      temp = temp / 16;
    }
    std::cout << hex;
  } else {
    temp = -temp;
    std::string hex = "";
    while (temp > 0) {
      int ostatok = temp % 16;
      char hexChar;
      if (ostatok < 10) {
        hexChar = '0' + ostatok;
      } else {
        hexChar = 'A' + (ostatok - 10);
      }
      hex = hexChar + hex;
      temp = temp / 16;
    }
    std::cout << "-" << hex;
  }

  std::cout << std::endl;

  return 0;
}