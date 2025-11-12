#include <iostream>

std::string checkSirakuz(int num) {
  while (num != 1) {
    if (num % 2 == 0) {
      num = num / 2;
    } else {
      num = ((num * 3) + 1) / 2;
    }
  }
  return "True";
}

int main() {
  std::cout << checkSirakuz(15) << std::endl;
  std::cout << checkSirakuz(16);
}
