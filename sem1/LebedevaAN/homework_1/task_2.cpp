#include <iostream>
using namespace std;

double getTrapezoidArea(double trapezoid_base_first, 
                        double trapezoid_base_second,
                        double trapezoid_height) {
    return (trapezoid_base_first + trapezoid_base_second) * trapezoid_height / 2.0;
}

int main() {
    double trapezoid_base_first;
    double trapezoid_base_second;
    double trapezoid_height;
  std::cout << "Enter the trapezoid bases' values to get its area\n";
  std::cin >> trapezoid_base_first >> trapezoid_base_second;
  std::cout << "Enter the trapezoid height's value to get its area\n";
  std::cin >> trapezoid_height;
  std::cout << getTrapezoidArea(trapezoid_base_first, trapezoid_base_second, trapezoid_height) << std::endl;
}
