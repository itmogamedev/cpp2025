#include <iostream>

int SquareArea()
{
  int side = 0;

  std::cout << "Input your side: ";
  std::cin >> side;

  return side * side;
}

int main()
{
  std::cout << SquareArea() << std::endl;
}