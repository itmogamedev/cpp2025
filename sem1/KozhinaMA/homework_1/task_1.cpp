#include <iostream>

int main() {
  int storonaKvadrata, s;

  std::cout << "Enter the side of the square: " << std::endl;
  std::cin >> storonaKvadrata;
  if (storonaKvadrata > 0) {
    s = storonaKvadrata * storonaKvadrata;
    std::cout << "s = " << s;
  }
}
