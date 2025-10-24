#include <iostream>
using namespace std;

int trapetzarea(int height, int a, int b) { return height * ((a + b) / 2); }

int main() {
  float height, a, b, area;
  cout << "this program calculates the area of your trapezoid!";
  cout << "\nheight: ";
  cin >> height;
  cout << "\na: ";
  cin >> a;
  cout << "\nb: ";
  cin >> b;
  area = trapetzarea(height, a, b);
  cout << "\narea = " << area;
  cout << endl;
  return 0;
}
