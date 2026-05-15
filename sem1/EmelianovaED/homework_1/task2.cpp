#include <iostream>
int trapezoidArea(int side_a, int side_b, int hight) {
  int area_tra = ((side_a + side_b) * hight) / 2;
  return area_tra;
}
int main() {
  int side_a = 24, side_b = 13, hight = 15;
  std::cout << trapezoidArea(side_a, side_b, hight);

  return 0;
}
