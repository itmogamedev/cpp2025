#include <iostream>
#include <string>

std::string convertToOctal(int num) {
  std::string str = "";
  while (num != 0) {
    str = (char)(num % 8 + 48) + str;
    num = num / 8;
  }
  return str;
}
std::string convertToHexadecimal(int num) {
  std::string str = "";
  std::string symbol = "";
  while (num != 0) {
    if ((num % 16) < 10) {
      symbol = (char)((num % 16) + 48);
    } else {
      symbol = (char)((num % 16) + 55);
    }
    num = num / 16;
    str = symbol + str;
  }
  return str;
}
int main() {
  int num;
  std::cout << "Enter the number in decimal form ";
  std::cin >> num;
  std::cout << "Number in octal system: " << convertToOctal(num) << std::endl;
  std::cout << "Number in hexadecimal system: " << convertToHexadecimal(num)
            << std::endl;
  return 0;
}
