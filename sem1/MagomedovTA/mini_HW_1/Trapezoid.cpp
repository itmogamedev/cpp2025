#include <iostream>

void areaTrapezoid(float a, float a2, float h) {
  float area = ((a + a2) / 2.0f) * h;
  std::cout << area;
}

int main() {
  int a, a2, h;

  std::cout << "base 1: ";
  std::cin >> a;

  std::cout << "base 2: ";
  std::cin >> a2;

  std::cout << "height: ";
  std::cin >> h;

  std::cout << "Area: ";
  areaTrapezoid(a, a2, h);

  return 0;
}
