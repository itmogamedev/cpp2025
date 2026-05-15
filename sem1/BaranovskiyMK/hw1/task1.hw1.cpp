#include <iostream>

float SquareArae(int a) 
{
  return a*a;
}

int main() {
  int input;
  std::cout << "Type side length: ";
  std::cin >> input;

  std::cout << "\nS = " << SquareArae(input) << "\n";
  return 0;
}