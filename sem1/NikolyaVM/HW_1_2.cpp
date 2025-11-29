#include<iostream>

int trapezoid_area (int height, int base1, int base2){
    return height*(base1+base2)/2;
};

int main(){
  int input1, input2, input3;
  std::cout << "Please, input height of trapezoid\n";
  std::cin >> input1; 
  std::cout << "Please, input length of one trapezoid base\n";
  std::cin >> input2;
  std::cout << "Please, input length of another trapezoid base\n";
  std::cin >> input3;
  std::cout << trapezoid_area(input1, input2, input3);
}