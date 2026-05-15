#include <iostream>

int trapezia(int a, int b, int height) { return (a + b) / 2 * height; }

int main() {
  int first_base, second_base, height;
  std::cout << "Please, type number for two bases of the trapezia" << std::endl;
  std::cin >> first_base >> second_base;
  std::cout << "Now type number for height of the trapezia" << std::endl;
  std::cin >> height;
  std::cout << "Trapezia area = " << trapezia(first_base, second_base, height)
       << std::endl;
  return 0;
}
