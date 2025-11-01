#include <iostream>

using std::cout;
using std::endl;

int main() {
  unsigned int num = 1;
  bool fg = num % 2 == 0;

  for (unsigned int i = 2; i < 10'000'000; i++) {
    // cout << num << " ";

    while (num != 1) {
      fg = num % 2 == 0;

      if (fg)
        num *= 0.5;
      else
        num = (num * 3 + 1) * 0.5;
    }

    // cout << num << endl;

    num = i;
  }

  cout << "Yea, It Works" << endl;
}
