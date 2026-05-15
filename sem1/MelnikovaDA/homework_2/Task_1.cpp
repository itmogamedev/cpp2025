#include <iostream>
#include <string>

std::string tns(int number, int base) {
  const char alf[] = "0123456789ABCDEF";
  if (number == 0) return "0";
  std::string res;
  bool otris = false;
  if (number < 0) {
    otris = true;
    number = -number;
  }
  while (number > 0) {
    res = alf[number % base] + res;
    number /= base;
  }
  if (otris) {
    res += '-';
  }
  return res;
}

int main() {
  int x;
  while (true) {
    std::cout << "Enter a number: ";
    std::cin >> x;
    std::string tns16x = tns(x, 16);
    std::string tns8x = tns(x, 8);
    std::cout << "This is a number in the hex system: " << tns16x << std::endl;
    std::cout << "This is a number in the oct system: " << tns8x << std::endl;
  }
}
