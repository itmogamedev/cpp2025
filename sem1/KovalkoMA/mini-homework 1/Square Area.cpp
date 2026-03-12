#include <iostream>

double square_area(double side) {
  return side * side;
}

int main() {
  double side;
  std::cout << "Please input the length of the side of your square: ";
  std::cin >> side;
  if (side < 0) {
    std::cout << "A square's side cannot be negative!\n";
    return 1;
  }
  double area = square_area(side);
  std::cout << "The area of your square = " << area << '\n';
  return 0;
}