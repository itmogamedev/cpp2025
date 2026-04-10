#include <cmath>
#include <iostream>
void F(int num, char answer[], int rad) {
  int k = 0;
  while (num) {
    int x = num % rad;
    answer[k++] = (x < 10) ? '0' + x : 'A' + x - 10;
    num /= rad;
  }
  answer[k] = 0;
  for (int i = 0; i < k / 2; i++) {
    int t = answer[i];
    answer[i] = answer[k - i - 1];
    answer[k - i - 1] = t;
  }
  for (int i = 0; answer[i] != '\0'; i++) {
    std::cout << answer[i];
  }
}

int main() {
  int num = 0;
  int rad = 0;
  char answer[256];
  setlocale(LC_ALL, "Russian");
  std::cout << "Введите натуральное число:\n";
  std::cin >> num;
  std::cout << "Число в восьмеричной системе: ";
  F(num, answer, 8);
  std::cout << "\nЧисло в шестнадцатиричной системе: ";
  F(num, answer, 16);
  return 0;
}
