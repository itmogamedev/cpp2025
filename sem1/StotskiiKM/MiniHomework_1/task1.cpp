#include <cmath>
#include <iostream>

double areaOfSquare() {
  double side;
  std::cout << "Please, enter the side of the square: ";
  std::cin >> side;
  std::cout << "The area of your square is: ";
  return pow(side, 2.0);
}

int main() { std::cout << areaOfSquare(); }
