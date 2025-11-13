#include <iostream>
using namespace std;

std::string convert(int x, int y) {
  std::string symbols = "0123456789ABCDEF";
  std::string result = "";

  if (x == 0) return 0;

  while (x > 0) {
    int leftover = x % y;
    result = symbols[leftover] + result;
    x /= y;
  }
  return result;
}

int main() {
  int a;
  cout << "enter a numb: ";
  cin >> a;
  cout << "in hex: " << convert(a, 16) << " " << "in oct: " << convert(a, 8);
}
