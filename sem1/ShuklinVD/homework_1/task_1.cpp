#include <iostream>
#include <locale>
float areaSquare(float side) {
  if (side > 0) {
    return side * side;
  } else {
    return 0;
  }
}
int main() {
  setlocale(LC_ALL, "");
  float square_side;
  std::cout << "Введи сторону квадрата ";
  std::cin >> square_side;
  if (areaSquare(square_side)) {
    std::cout << areaSquare(square_side) << " - площадь квадрата";
  } else {
    std::cout << "Ошибка: в геометрии нет чисел меньше 0 или 0 - размер стороны"
              << std::endl;
  }

  return 0;
}
