#include <iostream>

void area_square(int a) {
  int area = a * a;
  std::cout << area;
}

int main() {
  int a, a2, h;

  std::cout << "Square side: ";
  std::cin >> a;

  std::cout << "Area: ";
  area_square(a);

  return 0;
}
