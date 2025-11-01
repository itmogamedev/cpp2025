#include <iostream>

void areaSquare(int a) {
  int area = a * a;
  std::cout << area;
}

int main() {
  int a, a2, h;

  std::cout << "Square side: ";
  std::cin >> a;

  std::cout << "Area: ";
  areaSquare(a);

  return 0;
}
