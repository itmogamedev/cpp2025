#include <iostream>

void to_16(int num) {
  if (num == 0) return;
  to_16(num / 16);

  int ost = num % 16;
  if (ost < 10)
    std::cout << ost;
  else
    std::cout << char('A' + (ost - 10));
}
void to_8(int num) {
  if (num == 0) return;
  to_8(num / 8);
  std::cout << (num % 8);
}
int main() {
  int num;

  std::cout << "Enter your num: ";
  std::cin >> num;

  std::cout << "Hex: ";
  to_16(num);
  std::cout << std::endl;
  std::cout << "Oct: ";
  to_8(num);

  return 0;
}
