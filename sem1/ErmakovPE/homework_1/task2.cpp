#include <iostream>

float sqrTr(float a, float b, float h) { return (((a * b) / 2) * h); }

int main() {
  float a, b, h;
  std::cin >> a >> b >> h;
  std::cout << sqrTr(a, b, h);
}