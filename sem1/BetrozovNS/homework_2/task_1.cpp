#include <iostream>

int main() {
  int ten_num = 0;
  
  std::cout << "Изначальное десятичное число: ";
  std::cin >> ten_num;

  std::cout << "Тогда восьмиричный вид - " << std::oct << ten_num << std::endl;
  std::cout << "Тогда шестнадцатиричный вид - " << std::hex << ten_num << std::endl;
  
  return 0;
}

