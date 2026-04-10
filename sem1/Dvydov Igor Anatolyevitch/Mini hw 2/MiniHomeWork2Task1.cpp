

#include <iostream>
void to16And8System(const int x);
int main() {
  int x;
  std::cout << "input int: ";
  std::cin >> x;
  std::cout << std::endl;
  to16And8System(x);
}
void to16And8System(const int x) {
  std::string result = "";
  const std::string symbols = "0123456789abcdef";
  int temp_x = x;
  while (temp_x) {
    result = symbols[temp_x % 16] + result;
    temp_x /= 16;
  }
  std::cout << "in 16 system " << result << std::endl;
  temp_x = x;
  result = "";
  while (temp_x) {
    result = symbols[temp_x % 8] + result;
    temp_x /= 8;
  }
  std::cout << "in 8 system " << result << std::endl;
}
