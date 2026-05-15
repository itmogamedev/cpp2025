#include <iostream>

int S(int a, int b) {
  std::cout << "S = " << a * b;
  return 0;
}

int main() {
  int a, b;
  std::cout << "a = ";
  std::cin >> a;

  std::cout << "b = ";
  std::cin >> b;
  S(a, b);
}
