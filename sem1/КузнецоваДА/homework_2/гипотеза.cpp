#include<iostream>

int main(){
  int number = 0;
  std::cout << "Input a natural number ";
  std::cin >> number;

  if (number <= 0){
    std::cout << "Please, input a natural number.";
    return 1;
  }

  while (number!=1){
    if (number % 2 == 0){
        number /= 2;
    }
    
    else{
        number = (number * 3 + 1) / 2;
    }
  }

  std::cout << "The hypothesis is correct."; 
  return 0;
}
