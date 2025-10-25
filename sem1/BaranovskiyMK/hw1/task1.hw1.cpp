#include <iostream>

float S_sq(int a) 
{
  return a*a;
}

int main() {
  int input;
  std::cout << "Type side length: ";
  std::cin >> input;

  std::cout << "\nS = " << S_sq(input) << "\n";
  return 0;
}