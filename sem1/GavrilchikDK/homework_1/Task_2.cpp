#include <iostream>

int main() {
  int side_a;
  std::cout << "Enter the side a: ";
  std::cin >> side_a;
  int side_b;
  std::cout << "Enter the side b: ";
  std::cin >> side_b;
  int height;
  std::cout << "Enter the height h: ";
  std::cin >> height;
  int area = (side_a + side_b) / 2 * height;
  std::cout << "Answer: " << area << std::endl;
  return 0;
}