#include <iostream>
#include <string>
std::string dict = "0123456789ABCDEF";
std::string calcHex(int num) {
  std::string hex = "";
  while (num > 0) {
    hex = dict[num % 16] + hex;
    num /= 16;
  }
  return hex;
}
std::string calcOct(int num) {
  std::string oct = "";
  while (num > 0) {
    oct = dict[num % 8] + oct;
    num /= 8;
  }
  return oct;
}
int main() {
  int number = 0;
  std::string hex = "";
  std::string oct = "";
  std::cin >> number;
  hex = calcHex(number);
  oct = calcOct(number);
  std::cout << "hex " + hex << std::endl;
  std::cout << "oct " + oct;
}
