#include <bitset>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

// Функция для преобразования в шестнадцатеричную систему
std::string decimalToHex(int decimal) {
  std::stringstream ss;
  ss << std::hex << decimal;  // Используем манипулятор hex
  return ss.str();
}

// Функция для преобразования в восьмеричную систему
std::string decimalToOctal(int decimal) {
  std::stringstream ss;
  ss << std::oct << decimal;  // Используем манипулятор oct
  return ss.str();
}

int main() {
  int dec;
  std::string oct, hex;
  std::cout << "enter decimal number" << std::endl;
  std::cin >> dec;
  oct = decimalToOctal(dec);
  hex = decimalToHex(dec);
  std::cout << hex << std::endl << oct;
}
