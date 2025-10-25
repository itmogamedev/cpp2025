#include <iostream>
#include <string>

std::string numbConverter(int numb, bool eight) {
  if (numb == 0) return "0";
  std::string answer = "";
  char symbol_dict[] = "0123456789ABCDEF";
  int divider = eight ? 8 : 16;
  while (numb > 0) {
    int remainder = numb % divider;
    answer = symbol_dict[remainder] + answer;
    numb = numb / divider;
  }
  return answer;
}

int main() {
  int numb;
  int divider;
  std::cout << "Please, type number you wanna convert" << std::endl;
  std::cin >> numb;
  std::cout << "Now type 1 for oct system or 2 for hex system" << std::endl;
  while (true) {
    std::cin >> divider;
    if (divider == 1 || divider == 2) break;
    std::cout << "Try again, 1 for oct, 2 for hex" << std::endl;
  }
  bool eight = divider == 1;
  std::cout << "Your converted number = " << numbConverter(numb, eight) << std::endl;
  return 0;
}
