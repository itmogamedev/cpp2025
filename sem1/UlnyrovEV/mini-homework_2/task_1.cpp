#include <iostream>
#include <string>

std::string decimalToOctAndHex(int decimal) {
  std::string octDigits = "01234567";
  std::string hexDigits = "0123456789ABCDEF";
  std::string octRes;
  std::string hexRes;
  int oct = decimal;
  int hex = decimal;

  if (decimal > 0) {
    while (oct > 0) {
      octRes = octDigits[oct % 8] + octRes;
      oct /= 8;
    }
    while (hex > 0) {
      hexRes = hexDigits[hex % 16] + hexRes;
      hex /= 16;
    }

  } else if (decimal == 0) {
    octRes = "0";
    hexRes = "0";
  } else {
    octRes = "error";
    hexRes = "error";
  }
  return "oct: " + octRes + "\nhex: " + hexRes;
}

int main() {
  int decimal;
  std::cout << "Enter the decimal number: ";
  std::cin >> decimal;

  std::cout << decimalToOctAndHex(decimal) << "\n";

  return 0;
}
