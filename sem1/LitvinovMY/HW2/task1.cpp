#include<iostream>
#include<stdexcept>
#include<algorithm>

const static std::string kAlphabet = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

std::string convertToBase(int n, unsigned short base) {
  if (base >= kAlphabet.length())
    throw std::invalid_argument("Cannot exceed the the alphabet!");
  
  std::string result = "";
  bool neg = false;

  if (n < 0) {
    neg = true;
    n = -n;
  }

  while (n != 0) {
    result += kAlphabet[n % base];
    n = n / base;
  }

  std::reverse(result.begin(), result.end());
  if (neg) result = "-" + result;

  return result;
}

std::string convertToOct(int n) {
  return convertToBase(n, 8);
}

std::string convertToHex(int n) {
  return convertToBase(n, 16);
}

int main() {
  int n;
  std::cin >> n;
  std::cout << convertToOct(n) << std::endl << convertToHex(n) << std::endl;
}