#include <iostream>

int main() {
  int n;
  std::cout << "Input your number: ";
  std::cin >> n;
  if (n == 0) {
    std::cout << "You need input n>0!";
    return 1;
  }
  while (n != 1) {
    if (n % 2 == 0) {
      n /= 2;
    } else {
      n = (n * 3 + 1) / 2;
    }
    std::cout << "----> " << n;
  }
  std::cout << "All good, the theorem works!";
  return 0;
}