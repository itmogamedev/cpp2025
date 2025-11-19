#include <iostream>
using namespace std;

int main() {
  int number;
  int leftover;
  cout << "please enter a number: ";
  cin >> number;
  while (number > 1) {
    leftover = number % 2;
    switch (leftover) {
      case (0): {
        number = number / 2;
        cout << number << endl;
        break;
      }
      case (1): {
        number = number * 3 + 1;
        cout << number << endl;
        break;
      }
    }
  }
  cout << "the result is " << number;
}
