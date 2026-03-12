#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
int main() {
  std::cout << "Enter your number: ";
  int next, curr, ost;
  std::cin >> curr;
  while (curr > 1) {
    ost = curr % 2;
    switch (ost) {
      case 1:
        next = (curr * 3 + 1) / 2;
        std::cout << std::endl << "(" << curr << " * 3 + 1) / 2 = " << next;
        curr = next;
        break;
      default:
        next = curr / 2;
        std::cout << std::endl << curr << " / 2 = " << next;
        curr = next;
        break;
    }
  }
  return 0;
}
