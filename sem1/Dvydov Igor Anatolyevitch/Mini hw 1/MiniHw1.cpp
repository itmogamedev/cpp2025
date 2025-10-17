#include <iostream>
float sSquere(float x);
float sTrapezoid(float x, float y, float h);
int main() {
  int choise;
  float x;
  float y;
  float h;
  while (true) {
    std::cout << "press 1 for squre area\npress 2 for trapezoid area" << std::endl;
    std::cin >> choise;
    switch (choise) {
      case 1:
        std::cout << "input shape" << std::endl;
        std::cin >> x;
        std::cout << std::endl << "squre area = " << sSquere(x) << std::endl;
        break;
      case 2:
        std::cout << "input 1st shape" << std::endl;
        std::cin >> x;
        std::cout << "input 2nd shape" << std::endl;
        std::cin >> y;
        std::cout << "input hight" << std::endl;
        std::cin >> h;
        std::cout << std::endl << "trapezoid area = " << sTrapezoid(x,y,h) << std::endl;
        break;
      default:
        std::cout << "wrong input" << std::endl;
        break;
    }
  }
  return 0;
}
float sSquere(float x) {
  return x * x;
}
float sTrapezoid(float x, float y, float h) {
  return (x + y) / 2 * h;
}
