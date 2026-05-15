#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
int main() {
  std::cout << "Number in decimal: ";
  std::string res8 = "", res16 = "";
  int a8, a16, curr;
  std::cin >> a8;
  a16 = a8;
  while (a8 > 0) {
    curr = a8 % 8;
    res8 += std::to_string(curr);
    a8 /= 8;
  }
  std::reverse(res8.begin(), res8.end());
  while (a16 > 0) {
    curr = a16 % 8;
    switch (curr) {
      case 10:
        res16 += "a";
        break;
      case 11:
        res16 += "b";
        break;
      case 12:
        res16 += "c";
        break;
      case 13:
        res16 += "d";
        break;
      case 14:
        res16 += "e";
        break;
      case 15:
        res16 += "f";
        break;
      default:
        res16 += std::to_string(curr);
        a16 /= 16;
        break;
    }
  }
  std::reverse(res16.begin(), res16.end());
  std::cout << "Number in octal: " << res8 << std::endl
            << "Number in hexadecimal: " << res16 << std::endl;
}
