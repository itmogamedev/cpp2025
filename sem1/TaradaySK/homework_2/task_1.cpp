#include <iostream>
#include <string>
void sixteen(int num) {
  int remainder;
  std::string result = "";
  while (num > 0) {
    remainder = num % 16;
    if (remainder == 0) result = "0" + result;
    if (remainder == 1) result = "1" + result;
    if (remainder == 2) result = "2" + result;
    if (remainder == 3) result = "3" + result;
    if (remainder == 4) result = "4" + result;
    if (remainder == 5) result = "5" + result;
    if (remainder == 6) result = "6" + result;
    if (remainder == 7) result = "7" + result;
    if (remainder == 8) result = "8" + result;
    if (remainder == 9) result = "9" + result;
    if (remainder == 10) result = "A" + result;
    if (remainder == 11) result = "B" + result;
    if (remainder == 12) result = "C" + result;
    if (remainder == 13) result = "D" + result;
    if (remainder == 14) result = "E" + result;
    if (remainder == 15) result = "F" + result;
    num /= 16;
  }
  std::cout << result;
}
void eight(int num) {
  int remainder;
  std::string result = "";
  while (num > 0) {
    remainder = num % 8;
    if (remainder == 0) result = "0" + result;
    if (remainder == 1) result = "1" + result;
    if (remainder == 2) result = "2" + result;
    if (remainder == 3) result = "3" + result;
    if (remainder == 4) result = "4" + result;
    if (remainder == 5) result = "5" + result;
    if (remainder == 6) result = "6" + result;
    if (remainder == 7) result = "7" + result;
    num /= 8;
  }
  std::cout << result;
}
int main() {
  int num = 0;
  std::cout << "Write number: ";
  std::cin >> num;
  std::cout << "In 16 it: ";
  sixteen(num);
  std::cout << " In 8 it: ";
  eight(num);
}
