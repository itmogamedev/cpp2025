#include <iostream>
using namespace std;
int squarearea(int a) { return a * a; }
int main() {
  float len, area;
  cout << "this program calculates the area of your square!";
  cout << "\nlength of square: ";
  cin >> len;
  area = squarearea(len);
  cout << "\narea = " << area;
  cout << endl;
  return 0;
}
