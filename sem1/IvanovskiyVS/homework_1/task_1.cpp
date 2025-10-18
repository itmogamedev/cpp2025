
// Минидомашка 1
// Задача 1: Реализовать функцию, которая возвращает подсчет площади квадрата.

#include <iostream>
float areaSqare(float side_length) { return (side_length * side_length); }
int main() {
  std::cout << "Please, enter the side length of the square: ";
  float side_length;
  std::cin >> side_length;
  std::cout << "The area of the square is " << areaSqare(side_length)
            << std::endl;
  return 0;
}
