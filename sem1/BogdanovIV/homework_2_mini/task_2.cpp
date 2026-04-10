#include <iostream>

void sirakuz(unsigned int numb) {
  while (numb != 1) {
    std::cout << numb << "->";
    if (numb % 2 != 0) {
      numb *= 3;
      ++numb;
    }
    numb /= 2;
  }

  std::cout << '1';
}

int main() {
  int numb;
  while (true) {
    std::cout << "\nInput natural number : ";
    std::cin >> numb;
    std::cout << "Sirakuz say:\n";
    sirakuz(numb);
  }

  return 0;
}
