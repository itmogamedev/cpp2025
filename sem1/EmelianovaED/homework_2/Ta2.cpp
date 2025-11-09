#include <iostream>
int recSyracuse(int a) {
  if (a == 1) {
    return 1;
  } else if (a == 0) {
    return 0;
  } else if (a % 2 == 0) {
    recSyracuse(a / 2);
  } else {
    recSyracuse(((a * 3) + 1) / 2);
  }
}
int main() {
  int nat_num = 0;
  std::cin >> nat_num;
  if (recSyracuse(nat_num) == 1) {
    std::cout << "Hypothesis proven";
  } else {
    std::cout << "Hypothesis isn't proven";
  }
  return 0;
}
