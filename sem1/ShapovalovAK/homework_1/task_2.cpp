#include <iostream>
using namespace std;

double square_trapizoid(double a, double b, double h) {
  return (a + b) / 2 * h;
}

int main() {
  double a;
  double b;
  double h;
  cout << "First foundation length: ";
  cin >> a;
  cout << "Second foundation length: ";
  cin >> b;
  cout << "Height length: ";
  cin >> h;
  while (a < 0 || b < 0 || h < 0) {
    cout << "Invalid input. Can be only positive values" << endl;
    cout << "First foundation length: ";
    cin >> a;
    cout << "Second foundation length: ";
    cin >> b;
    cout << "Height length: ";
    cin >> h;
  }
  cout << square_trapizoid(a, b, h) << endl;
}
