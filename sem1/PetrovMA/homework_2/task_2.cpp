///<summary>Proves a syracuse theorem for a specified number</summary>
int doSyracuse(int input) {
  if (input <= 0)
    return -1;

  while (input != 1) {
    if (input % 2 == 0)
      input /= 2;
    else
      input = ((input * 3) + 1) / 2;
  }

  return input;
}

// Sample usage
#include <iostream>
#include <cassert>

int main() {
  assert((doSyracuse(14912) == 1));
  assert((doSyracuse(-124) == -1));

  int v;
  std::cout << "Input a number to prove the theorem for: ";
  std::cin >> v;
  int syra = doSyracuse(v);
  if (syra == -1) {
    std::cout << "You did not enter a natural number!";
    return -1;
  }
  std::cout << "Syracuse proven: " << (syra == 1);
  return 0;
}
