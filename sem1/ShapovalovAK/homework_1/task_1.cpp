#include <iostream>
using namespace std;

double square(double a) {
  if (a > 0) {
    cout << "Square of side " << a << ": ";
    return a * a;
  } else
    return 0;
}
int main() {
  double x;
  cout << "enter squer side lenght: ";
  cin >> x;

  cout << square(x) << endl;
}
