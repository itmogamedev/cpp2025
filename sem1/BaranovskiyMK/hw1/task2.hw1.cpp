#include <iostream>

float TrapezoidАrea(float a, float b, float s)
{
  return 0.5 * (a + b) * s;
}

int main() {
  int input1, input2, input3;
    
  std::cout << "Tipe sid's and hight lengths ";
  std::cin >> input1 >> input2 >> input3;

  std::cout << std::endl << "S = " << TrapezoidАrea(input1, input2, input3) << "\n";
}