#include <iostream>

int main() {
  int a, b, h = 0;

  while (true) {
    std::cout << "Input side a:" << std::endl;
    std::cin >> a;
    std::cout << "Input side b:" << std::endl;
    std::cin >> b;
    std::cout << "Input h:" << std::endl;
    std::cin >> h;
    int S = (a + b) / 2 * h;
    std::cout << "S = " << S << std::endl;
  }
}
