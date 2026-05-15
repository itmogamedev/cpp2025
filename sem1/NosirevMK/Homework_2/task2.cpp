#include <iostream>
using namespace std;
int main() {
  int number;
  cout << "Enter number ";
  cin >> number;
  cout << "sequence: " << number;
  int steps = 0;
  while (number != 1) {
      if (number % 2 == 0) {
          number = number / 2;
      }
      else {
          number = (3 * number + 1) / 2;
      }
      cout << " -> " << number << std::endl;
      steps++;
      if (steps > 1000) {
          cout << "Too many steps" << std::endl;
          break;
      }
  }
  if (number == 1) {
      cout << "Done. Reachet goal in " << steps << " steps";
  }
  return 0;
}