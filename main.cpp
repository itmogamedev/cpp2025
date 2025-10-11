#include <bits/stdc++.h>

int main() {
    std::cout << "Please enter one number (side of a square) to calculate area of the square\n";
    std::cout << "Or enter three numbers (bases of a trapezoid THEN its height) to calculate area of the trapezoid\n";
  double area[3];
  int count = 0;
  while (std::cin >> area[count]) {
      ++count;
      if (count > 3) {
          std::cerr << "Error: invalid input\n";
          exit(1);
      }
  }
  
  if (count == 2 or count == 0) {
          std::cerr << "Error: invalid input\n";
          exit(1);
      }
      
      std::cout << ((count == 1) ? (area[0]*area[0]) : 
      (area[2] * (area[0] + area[1]) / 2.0)) << std::endl;
}
