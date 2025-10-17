#include <iostream>
using namespace std;

double getSquareArea(double square_side_value) {
    return square_side_value * square_side_value;
}

int main() {
    double square_side_value;
  std::cout << "Enter a square's side value\n";
  std::cin >> square_side_value;
  std::cout << getSquareArea(square_side_value) << std::endl;
}
