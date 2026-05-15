#include <iostream>
#pragma once

float sSquare(float side)
{
  return side * side;
}

int main()
{
  float a;
  std::cin >> a;
  std::cout << sSquare(a);
}
