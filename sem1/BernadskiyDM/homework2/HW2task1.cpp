// Простой вариант

// #include <iostream>
// int main() {
//   int number;
//   std::cout<<"Enter your number";
//   std::cin >> number;
//   std::cout<<"Your number in hexadecimal is ";
//   std::cout << std::hex << number << std::endl;
//   std::cout<<"Your number in octal number system is ";
//   std::cout << std::oct << number << std::endl;
//   return 0;
// }

// Усложнённый вариант
#include <iostream>
#include <string>

std::string to_oct(int num) {
  std::string oct_num = "";

  while (num != 0) {
    oct_num = std::to_string(num % 8) + oct_num;
    num /= 8;
  }
  return oct_num;
}

std::string to_hex(int num) {
  std::string hex_num = "";
  const char hex_mas[] = "0123456789ABCDEF";

  while (num != 0) {
    hex_num = hex_mas[num % 16] + hex_num;
    num /= 16;
  }
  return hex_num;
}

int main() {
  int number;
  std::cout<< "Entrer your number";
  std::cin >> number;

  std::cout << "Your number in octal number system is "<< to_oct(number)<< std::endl;
  std::cout << "Your number in hexadecimal is "<< to_hex(number);
  return 0;
}
