#include <iostream>
using namespace std;

float SquareArea()
{
  int side = 0;

  cout << "Input your side: ";
  cin >> side;

  return side * side;
}

int main()
{
  cout << SquareArea() << endl;
}