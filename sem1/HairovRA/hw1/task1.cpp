#include <iostream>

int squareArea(int n) {
  n = n * n;
  return n;
}

int main() {
  int n;
  std::cout << "enter number" << std::endl;
  std::cin >> n;
  n = squareArea(n);

  std::cout << n;
}
