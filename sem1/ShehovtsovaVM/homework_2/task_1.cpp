#include <iostream>
using namespace std;

void convertFromDecimalToOctal(int a) {
  int oct[1000];
  int i = 0;
  while (a != 0) {
    oct[i] = a % 8;
    a = a / 8;
    i++;
  }
  cout << "number in oct: ";
  for (int j = i - 1; j >= 0; j--) {
    cout << oct[j];
  }
  cout << endl;
}
void convertFromDecimalToHexadecimal(int a) {
  int hex[1000];
  int i = 0;
  while (a != 0) {
    hex[i] = a % 16;
    a = a / 16;
    i++;
  }
  cout << "number in hex: ";
  for (int j = i - 1; j >= 0; j--) {
    cout << hex[j];
  }
  cout << endl;
}
int main()
{
  int a;
  cin >> a;
  convertFromDecimalToOctal(a);
  convertFromDecimalToHexadecimal(a);
  return 0;
}
