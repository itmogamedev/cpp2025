#include <iostream>
#include <locale>
float areaTrapezoid(float big_side, float small_side, float height) {
  if (big_side > 0 and small_side > 0 and height > 0) {
    return 0.5 * (big_side + small_side) * height;
  } else {
    return 0;
  }
}
int main() {
  setlocale(LC_ALL, "");
  float trapezoid_big_side;
  float trapezoid_small_side;
  float trapezoid_height;
  std::cout << "Введи большую сторону трапеции ";
  std::cin >> trapezoid_big_side;
  std::cout << "Введи малую сторону трапеции ";
  std::cin >> trapezoid_small_side;
  std::cout << "Введи высоту сторону трапеции ";
  std::cin >> trapezoid_height;
  if (areaTrapezoid(trapezoid_big_side, trapezoid_small_side,
                    trapezoid_height)) {
    std::cout << areaTrapezoid(trapezoid_big_side, trapezoid_small_side,
                               trapezoid_height)
              << " - площадь трапеции";
  } else {
    std::cout
        << "Ошибка: в геометрии нет чисел меньше 0 или 0 - размер стороны";
  }
  return 0;
}
