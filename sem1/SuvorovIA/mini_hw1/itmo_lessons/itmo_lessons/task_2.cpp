#include <iostream>
using namespace std;

float trapezoid_area()
{
  float side_1 = 0;
  float side_2 = 0;
  float height = 0;
  float area = 0;

  cout << "Input your 1 side: ";
  cin >> side_1;

  cout << "Input your 2 side: ";
  cin >> side_2;

  cout << "Input your height: ";
  cin >> height;

  area = (side_1 + side_2) / 2 * height;
  return area;
}

int main()
{
  cout << trapezoid_area() << endl;
}