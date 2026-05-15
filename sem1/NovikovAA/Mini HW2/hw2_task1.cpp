#include <iostream>
int main() {
  int numdec, numhex, numoct = 0;
  std::cout << "Input the decimal number:" << std::endl;
  std::cin >> numdec;
  std::cout << "Hexadecimal: " << std::hex << numdec << std::endl;
  std::cout << "Octagonal: " << std::oct << numdec << std::endl;
  return 0;
}
