#include <iostream>

float trapezoidArea(float n, float n1, float n2) {
  n = (n + n1) / 2 * n2;
  return n;
}

int main() {
  float n, n1, n2;
  float s;
  std::cout << "enter numbers, s1,s2,h" << std::endl;
  std::cin >> n >> n1 >> n2;
  std::cout << std::endl;
  s = trapezoidArea(n, n1, n2);

  std::cout << s;
}
