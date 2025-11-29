#include<iostream>

int square_area(int length){
  return length*length;
};

int main(){
  int input;
  std::cout << "Please, input length of the square\n";
  std::cin >> input;
  std::cout << square_area(input);
}