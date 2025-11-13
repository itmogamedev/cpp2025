#include <iostream>

void toHex(int num) {
  if (num == 0) return;
  toHex(num / 16);

  int ost = num % 16;
  if (ost < 10)
    std::cout << ost;
  else
    std::cout << char('A' + (ost - 10));
}
void toOct(int num) {
  if (num == 0) return;
  toOct(num / 8);
  std::cout << (num % 8);
}
int main() {
  int num;

  std::cout << "Enter your num: ";
  std::cin >> num;

  std::cout << "Hex: ";
  toHex(num);
  std::cout << std::endl;
  std::cout << "Oct: ";
  toOct(num);

  return 0;
}
