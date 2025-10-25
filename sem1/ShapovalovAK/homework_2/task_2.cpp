#include <iostream>
using namespace std;

int main() {
  int a;
  cout << "enter a natural numb: ";
  cin >> a;
  while (a >= 1) {
    if (a % 2 == 0) {
      a = a / 2;
    } else {
      a = (a * 3 + 1) / 2;
    }
    if (a == 1) {
      cout << "hypothesis is true";
      break;
    }
  }
}
