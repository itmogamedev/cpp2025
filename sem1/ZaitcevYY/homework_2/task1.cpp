#include <iostream>

std::string converterHex(const int num) {
  std::string result = "";
  const std::string symbols = "0123456789abcdef";
  int temp_num = num;

  while (temp_num) {
    result = symbols[temp_num % 16] + result;
    temp_num /= 16;
  }
  return result;
}

std::string converterOct(const int num) {
  std::string result = "";
  const std::string symbols = "01234567";
  int temp_num = num;

  while (temp_num) {
    result = symbols[temp_num % 8] + result;
    temp_num /= 8;
  }
  return result;
}

int main() {
  std::cout << "15 to base 16: " << converterHex(15) << std::endl;
  std::cout << "15 to base 8: " << converterOct(15);
}
