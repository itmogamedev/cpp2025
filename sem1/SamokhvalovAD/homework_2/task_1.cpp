#include <iostream>

std::string toOctal(int num) {
  std::string answer = "", alf = "012345678";
  while (num > 0) {
    answer = alf[num % 8] + answer;
    num /= 8;
  }
  return answer == "" ? "0" : answer;
}

std::string toHexadecimal(int num) {
  std::string answer = "", alf = "0123456789ABCDEF";
  while (num > 0) {
    answer = alf[num % 16] + answer;
    num /= 16;
  }
  return answer == "" ? "0" : answer;
}

int main() {
  int num;
  std::cout << "Enter the number: ";
  std::cin >> num;
  std::cout << "This number in octal system: " << toOctal(num) << "\n"
            << "This number in hexadecimal system: " << toHexadecimal(num);
  return 0;
}