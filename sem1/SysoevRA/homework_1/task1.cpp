#include <iostream>

int main() {
  double n;
  std::cin >> n;
  if (n > 0) {
    std::cout << n * n;
  } else {
    std::cout << "write a number greater than 0" << std::endl;
  }
}
