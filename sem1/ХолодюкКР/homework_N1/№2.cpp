#include <iostream>

int main() {
  float S = 0;
  float h = 0;
  float a = 0;
  float b = 0;
  std::cout << "enter the length of the height: ";
  std::cin >> h;
  std::cout << "enter the length of the smaller base: ";
  std::cin >> a;
  std::cout << "enter the length of the larger base: ";
  std::cin >> b;
  S = 0.5 * (a + b) * h;
  std::cout << S;
}
