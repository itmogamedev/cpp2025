

#include <iostream>
void sircaus(int x);
int main() {
  int x;
  while (true) {
    std::cout << "input int: ";
    std::cin >> x;
    std::cout << std::endl;
    sircaus(x);
  }
    
}
void sircaus(int x) {
  while (x != 1) {
    if (x % 2) {
      x = (x * 3 + 1) / 2;
      std::cout << x << std::endl;
    }
    else {
      x = x / 2;
      std::cout << x << std::endl;
    }
  }
}