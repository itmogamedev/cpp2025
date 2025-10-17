#include <iostream>
using namespace std;

int collatz(int numb) {
  if (numb == 1) return 1;
  if (numb % 2 == 0)
    return collatz(numb / 2);
  else
    return collatz(((numb * 3) + 1) / 2);
}

int main() {
  int numb;
  cout << "Type the number you want to check for Collatz conjecture" << endl;
  while (true) {
    cin >> numb;
    if (numb > 0) break;
    cout << "Please type something more then 0" << endl;
  }

  cout << "Your number = " << collatz(numb) << endl;
  return 0;
}
