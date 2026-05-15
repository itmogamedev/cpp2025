#include <iostream>
#pragma once

float sTrapezoid(float a, float b, float h)
{
  return (a + b) / 2 * h;
}

int main()
{
  float a, b, h;
  std::cin >> a >> b >> h;
  std::cout << sTrapezoid(a, b, h);
}
