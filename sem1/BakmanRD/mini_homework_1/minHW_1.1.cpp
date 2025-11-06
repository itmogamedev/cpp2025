#include <iostream>

int main() {
  int a = 0;
  std::cout << "please enter the side of the square : ";
  std::cin >> a;
  while (a < 0) {
    std::cout << "please enter a positive side of the square, the previous one "
                 "was less then zero : ";
    std::cin >> a;
  }
  std::cout << "the area of the square is: " << a * a;
}
