#include <iostream>

void square_area(int side1){
  std::cout << "Площадь = " << side1 * side1 << std::endl;
}

int main() {
  int side1;
  std::cout << "Введите сторону квадрата: ";
  std::cin >> side1;
  square_area(side1);
  return 0;
}