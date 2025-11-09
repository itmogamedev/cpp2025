#include <iostream>
int func(int num) {
  if (num % 2 == 0) {
    return num / 2;
  } else {
    return ((num * 3) + 1) / 2;
  }
}
int main() {
  int nat = 0;
  std::cout << "Input a natural number:" << std::endl;
  std::cin >> nat;
  int result = func(nat);
  while (result != 1) {
    std::cout << result << std::endl;
    result = func(result);
  }

  std::cout << result << std::endl;
  std::cout << "The hypothesis is true" << std::endl;
  return 0;
}
