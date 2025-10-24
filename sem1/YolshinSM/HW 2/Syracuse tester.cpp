#include <iostream>

int main() {
  int a = 0;
  int i = 0;
  std::cout << "Enter number: ";
  std::cin >> a;
  while (a != 1) {
    i++;
    if (a % 2 == 0) {
      a /= 2;
    } else {
      a = (a * 3 + 1) / 2;
    }
    std::cout << a << " ";
  }
  std::cout << "\nIt works!\n" << i << " transformations were required!";
}
