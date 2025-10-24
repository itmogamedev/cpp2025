#include <iostream>

std::string to_octal(int num) {
  std::string answer = "", alf = "012345678";
  while (num > 0) {
    answer = alf[num % 8] + answer;
    num /= 8;
  }
  return answer == "" ? "0" : answer;
}

std::string to_hexadecimal(int num) {
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
  std::cout << "This number in octal system: " << to_octal(num) << "\n"
            << "This number in hexadecimal system: " << to_hexadecimal(num);
  return 0;
}