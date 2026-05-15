#include <iostream>
#include <locale>

float sOfTrapezoid(float a, float b, float h);

int main() {
  setlocale(LC_CTYPE, "Russian");
  float a = 0;
  float b = 0;
  float h = 0;

  std::cout << "Введите длину оснований трапеции через пробел: " << std::endl;
  std::cin >> a >> b;
  std::cout << "Введите высоту трапеции: ";
  std::cin >> h;
  std::cout << "Площадь трапеции: " << sOfTrapezoid(a, b, h);

  return 0;
}

float sOfTrapezoid(float a, float b, float h) {
  return (a + b) / 2 * h;
}
