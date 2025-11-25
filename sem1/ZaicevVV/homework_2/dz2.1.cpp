#include <iostream>

bool checkSirakuzHypothesis(int num) {
  while (num > 0) {
    if (num % 2 == 0) {
      num /= 2;
    } else {
      num = (num * 3 + 1) / 2;
    }

    if (num == 1) {
      return 1;
    }
  }
  return 0;
}

int main() { return 0; }
