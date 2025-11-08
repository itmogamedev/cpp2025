#include <iostream>

int square(int side_a) { return side_a * side_a; }

int main() {
  int num_to_square;
  std::cout << "Enter the number to square it: ";
  std::cin >> num_to_square;
  std::cout << "The square of " << num_to_square << " is "
            << square(num_to_square) << "\n";
  return 0;
}