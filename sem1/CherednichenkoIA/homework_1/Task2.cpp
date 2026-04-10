#include <iostream>

int S(int a, int b, int h) {
  cout << ((a + b) * h) / 2;
  return 0;
}

int main() {
  setlocale(LC_ALL, "rus");
  int a, b, h;
  std::cout << "a = ";
  std::cin >> a;
  std::cout << "b = ";
  std::cin >> b;
  std::cout << "h = ";
  std::cin >> h;

  std::cout << "S = ";

  S(a, b, h);
}
