#include <iostream>

double squareArea(double a) {
  if (a > 0) {
    std::cout << "Area of square = ";
    return a * a;
  } else {
    std::cout << "Unfortunately, you have been banned." << std::endl;
    std::exit(0);
  }
}

int main() {
  double a = 0;
  std::cout << "Enter side length of your square: ";
  std::cin >> a;
  std::cout << squareArea(a) << std::endl;
  return 0;
}