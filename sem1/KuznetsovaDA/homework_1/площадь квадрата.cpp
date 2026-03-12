#include <iostream>

int main(){
  int side_length = 0;
  std::cout << "The side of the square equals ";
  std::cin >> side_length;

  const int area = side_length * side_length;
  std::cout << "\n" << "The area of the square equals " << area << "." << std::endl;

  return 0;
}