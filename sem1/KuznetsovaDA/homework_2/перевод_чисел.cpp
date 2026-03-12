#include<iostream>
#include<string>

void convert_number(int number){
  std::string number_oct = "";
  std::string number_hex = "";

   if (number == 0){
    number_oct = "0";
    number_hex = "0";
  }
  
  int temp_number = number;
  while (temp_number > 0){
    number_oct = std::to_string(temp_number % 8) + number_oct;
    temp_number /= 8;
  }

  while (number > 0){
    if ((number % 16) < 10){
      number_hex = std::to_string(number % 16) + number_hex;
    }
    
    else{
      std::string letters[6] = {"A","B","C","D","E","F"};
      number_hex = letters[number % 16 - 10] + number_hex;
    }
    number /= 16;
  }
  std::cout << "Oct = " << number_oct << std::endl;
  std::cout << "Hex = " << number_hex << std::endl;
}

int main(){
  int number = 0;
  std::cout << "Input the number: ";

  std::cin >> number;
  convert_number(number);
  
  return 0;
}

