#include <iostream>
int up_side = 0;
int dn_side = 0;
int high = 0;
float trapez = 0;
float calc_s(int up_side, int dn_side, int high) {
  return (up_side + dn_side) * high / 2.;
}
int main() {
  std::cin >> up_side;
  std::cin >> dn_side;
  std::cin >> high;
  trapez = calc_s(up_side, dn_side, high);
  std::cout << trapez;
}
