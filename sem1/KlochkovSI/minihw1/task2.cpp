#include <iostream>
int TrapezoidArea(int side_a, int side_b, int height) {
  int tra_area = ((side_a + side_b) * height) / 2;
  return tra_area;
}
int main() {
  int side_a, side_b, height = 0;
  std::cout << "Enter side_a lenght" << std::endl;
  std::cin >> side_a;
  std::cout << "Enter side_b lenght" << std::endl;
  std::cin >> side_b;
  std::cout << "Enter height lenght" << std::endl;
  std::cin >> height;
  std::cout << TrapezoidArea(side_a, side_b, height);
  return 0;
}
