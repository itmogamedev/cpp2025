#include <iostream>


float calculateSquareArea(float a) {
  return a * a;
}

int main()
{
  float a;
  std::cin >> a;
  std::cout << calculateSquareArea(a);
}
