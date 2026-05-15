#include <iostream>

float square(float a, float b, float h) { return (((a + b) / 2) * h); }

int main() {
  std::cout << "Enter the two bases of the trapezoid and the height separated "
               "by a space:\n";
  float a, b, h = 0;

  std::cin >> a >> b >> h;

  float s = square(a, b, h);

  std::cout << "Trapezoid area = " << s;

  return 0;
}