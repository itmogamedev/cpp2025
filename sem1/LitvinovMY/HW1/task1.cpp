#include<iostream>

int computeSquareArea(int side) {
  return side * side;
}

int main() {
  int a;
  std::cout << "Введите длину стороны: ";
  std::cin >> a;
  std::cout << std::endl << "Площадь квадрата: " << computeSquareArea(a) << endl;

  return 0;
}
