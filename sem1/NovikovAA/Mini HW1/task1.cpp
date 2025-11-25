#include <iostream>

int main() {
  int a = 0;

  while (true) {
    std::cout << "Input the square's side length:" << std::endl;
    std::cin >> a;
    int S = a * a;
    std::cout << "S = " << S << std::endl;
  }
}
