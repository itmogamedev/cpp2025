#include <iostream>
#include <string>
std::string hexSystem(int a) {
  char hex_alf[16] = {'0', '1', '2', '3', '4', '5', '6', '7',
                      '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
  std::string hex_num = "";
  while (a > 0) {
    hex_num = hex_alf[a % 16] + hex_num;
    a = a / 16;
  }
  return hex_num;
}
std::string octSystem(int a) {
  char oct_alf[8] = {'0', '1', '2', '3', '4', '5', '6', '7'};
  std::string oct_num = "";
  while (a > 0) {
    oct_num = oct_alf[a % 8] + oct_num;
    a = a / 8;
  }
  return oct_num;
}
int main() {
  int num_pr = 0;
  std::cin >> num_pr;
  std::cout << hexSystem(num_pr) << ' ' << octSystem(num_pr);
  return 0;
}
