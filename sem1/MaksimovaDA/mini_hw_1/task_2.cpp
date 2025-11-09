#include <iostream>
int main() {
  double a_trapeze = 0;
  double b_trapeze = 0;
  double h_trapeze = 0;
  std::cout << "smaller trapezoid base: ";
  std::cin >> a_trapeze;
  std::cout << "larger trapezoid base: ";
  std::cin >> b_trapeze;
  std::cout << "trapezoid height: ";
  std::cin >> h_trapeze;
  double s_trapeze = ((a_trapeze + b_trapeze) / 2) * (h_trapeze);
  std::cout << "S = ";
  std::cout << s_trapeze << std::endl;
}