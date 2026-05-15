#include <iostream>
double squareArea(double side) {
  return side * side;
}
int main() {
  double side = 5.0;
  
  std::cout << "Площадь квадрата: " << squareArea(side);
  
  return 0;
}