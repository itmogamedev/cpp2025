#include <iostream>
#include <string>

std::string dectooct(int dec) {
  std::string octsymb = "01234567";
  std::string octres;

  while (dec > 0) {
    octres = octsymb[dec % 8] + octres;
    dec /= 8;
  }

  return octres;
}

std::string dectohex(int dec) {
  std::string hexsymb = "0123456789ABCDEF";
  std::string hexres;

  while (dec > 0) {
    hexres = hexsymb[dec % 16] + hexres;
    dec /= 16;
  }

  return hexres;
}

int main() {
  std::cout << "This program converts your dec number to hex and oct cc!";
  std::cout << "\nEnter your number:\n";
  int urdec;
  std::cin >> urdec;
  std::cout << "\nNumber in oct cc: \n" << dectooct(urdec);
  std::cout << "\nNumber in hex cc: \n" << dectohex(urdec);

  return 0;
}
