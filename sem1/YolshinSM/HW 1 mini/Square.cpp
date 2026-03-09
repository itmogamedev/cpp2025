#include <iostream>

int square(int a) { return a * a; }

int main() {
  int a = 0;
  std::cout << "Enter side: ";
  std::cin >> a;
  std::cout << "Area of square: ";
  std::cout << square(a);
}
