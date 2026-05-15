#include <iostream>

float squareArea(float a);
float trapezoidArea(float a, float b, float h);
void interactSquareArea();
void interactTrapezoidArea();

int main() {
  interactSquareArea();
  std::cout << "---" << std::endl;
  interactTrapezoidArea();
  return 0;
}

float squareArea(float a) { return a * a; }

void interactSquareArea() {
  float a_side = 0;

  std::cout << "Square area" << std::endl;
  std::cout << "Input side: ";
  std::cin >> a_side;

  std::cout << "Square area is " << squareArea(a_side) << std::endl;
}

float trapezoidArea(float a, float b, float h) { return ((a + b) / 2.0) * h; }

void interactTrapezoidArea() {
  float a_side = 0;
  float b_side = 0;
  float h_size = 0;

  std::cout << "Trapezoid area" << std::endl;
  std::cout << "Input first basis: ";
  std::cin >> a_side;

  std::cout << "Input second basis: ";
  std::cin >> b_side;

  std::cout << "Input trapezoid height: ";
  std::cin >> h_size;

  std::cout << "Trapezoid area is " << trapezoidArea(a_side, b_side, h_size)
            << std::endl;
}
