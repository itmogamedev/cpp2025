#include <iostream>

void syracuseFunction(int x) {
  while (x != 1) {
    if (x % 2 == 1) {
      x = x * 3 + 1;
    }
    x /= 2;
  }
}

int main() {
  std::cout << "Input your max integer to test Syracuse problem. If it is "
               "solved, the program will finish."
            << std::endl;
  int integer;
  std::cin >> integer;
  for (int i = 1; i < integer; i++) {
    syracuseFunction(i);
  }
}
