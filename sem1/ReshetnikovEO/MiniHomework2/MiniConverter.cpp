#include <iostream>
using namespace std;
#include <string>

string numb_converter(int numb, bool eight) {
  if (numb == 0) return "0";
  string answer = "";
  char symbol_dict[] = "0123456789ABCDEF";
  int divider = eight ? 8 : 16;
  while (numb > 0) {
    int remainder = numb % divider;
    answer = symbol_dict[remainder] + answer;
    numb = numb / divider;
  }
  return answer;
}

int main() {
  int numb;
  int divider;
  cout << "Please, type number you wanna convert" << endl;
  cin >> numb;
  cout << "Now type 1 for oct system or 2 for hex system" << endl;
  while (true) {
    cin >> divider;
    if (divider == 1 || divider == 2) break;
    cout << "Try again, 1 for oct, 2 for hex" << endl;
  }
  bool eight = divider == 1;
  cout << "Your converted number = " << numb_converter(numb, eight) << endl;
  return 0;
}
