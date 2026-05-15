#include <algorithm>  //для работы reverse
#include <iostream>
#include <string>

std::string conversionToOctal(int number);
std::string conversionToHexadecimal(int number);

int main() {
  setlocale(LC_ALL, "Russian");
  int number;
  std::cout << "Число в десятичной системе: ";
  std::cin >> number;

  std::cout << "Число в восьмиричной сc: " << conversionToOctal(number)
            << std::endl;
  std::cout << "Число в шестнадцатеричной сc: "
            << conversionToHexadecimal(number);
  return 0;
}

std::string conversionToOctal(int number) {
  std::string octal;

  while (number > 0) {
    octal += std::to_string(number % 8);
    number /= 8;
  }
  reverse(octal.begin(),
          octal.end());  // реверс в строчке от первого до последнего символа
  return octal;
}

std::string conversionToHexadecimal(int number) {
  std::string alphabet = "0123456789ABCDEF";
  std::string hexadecimal;

  while (number > 0) {
    hexadecimal += alphabet[number % 16];
    number /= 16;
  }
  reverse(hexadecimal.begin(), hexadecimal.end());
  return hexadecimal;
}
