#include <iostream>

int main() {
  int a, i = 0;
  std::cin >> a;
  while (a != 1) {
    if (a % 2 == 0) {
      a /= 2;
      i++;
    } else {
      a *= 3;
      a++;
      a /= 2;
      i++;
    }
  }
  std::cout << i;
}