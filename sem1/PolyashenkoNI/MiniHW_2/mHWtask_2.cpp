#include <iostream>

int main (){
  long long int natural = 0;

  std::cout << "Enter your num: ";
  
  if (!(std::cin >> natural)){
    std::cout << "You have been banned :(" << std::endl;
    return 1;
  }

  if (natural <= 0){
    std::cout << "Please, enter positive number"<< std::endl;
    return 2;
  }

  while (natural != 1){
    if (natural % 2 == 0){
      natural /= 2;
      std::cout << natural << std::endl;
    }

    else {
      natural = (natural * 3 + 1) / 2; 
      std::cout << natural << std::endl;
    }
  }
}