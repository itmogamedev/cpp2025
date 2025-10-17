#include <iostream>

float Trapeze(float base_a, float base_b, float height) {
  return 0.5 * (base_a + base_b) * height;
}

int main() {
  setlocale(LC_ALL, "Russian");

  std::cout << "Введите длины оснований трапеции и высоту соответственно "
               "(через Enter): ";

  int base_a, base_b, height;
  std::cin >> base_a >> base_b >> height;

  float res;
  res = Trapeze(base_a, base_b, height);
  std::cout << res;

  return 0;
}
