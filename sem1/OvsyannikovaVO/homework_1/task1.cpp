#include <iostream>

int squarearea(int a) { return a * a; }
int main() {
  float len, area;
  std::cout << "this program calculates the area of your square!";
  std::cout << "\nlength of square: ";
  std::cin >> len;
  area = squarearea(len);
  std::cout << "\narea = " << area;
  std::cout << std::endl;
  return 0;
}
