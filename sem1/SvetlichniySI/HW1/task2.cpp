#include <iostream>
#include <cmath>

int main() {
  double s, a, b, c, d;
  std::cout << "vvedite men'shee osnovanie, bol'shee osnovenie, storoni" << std::endl;
  std::cin >> a >> b >> c >> d;
  s = ((a + b) / 2) * sqrt(pow(c, 2) - pow((pow(b - a, 2) + pow(c, 2) - pow(d, 2)) / (2 * (b - a)), 2));
  std::cout << s;
}
