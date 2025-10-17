#include <iostream>
using namespace std;

int trapezia(int a, int b, int height) { return (a + b) / 2 * height; }

int main() {
  int first_base, second_base, height;
  cout << "Please, type number for two bases of the trapezia" << endl;
  cin >> first_base >> second_base >> ;
  cout << "Now type number for height of the trapezia" << endl;
  cin >> height;
  cout << "Trapezia area = " << trapezia(first_base, second_base, height)
       << endl;
  return 0;
}
