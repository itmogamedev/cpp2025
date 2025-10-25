#include <iostream>

void from_dec_in_hex(int a){
  std::cout << std::hex << a << std::endl; 
}

void from_dec_in_oct(int b){
  std::cout << std::oct << b << std::endl;
}

int main(){
  int a;
  int b;
  std::cout << "Введите десятичное число для перевода в шестнадцатиричную: ";
  std::cin >> a;
  from_dec_in_hex(a);
  std::cout << "Введите десятичное число для перевода в восьмиричную: ";
  std::cin >> b;
  from_dec_in_oct(b);
  return 0;
}