#include <iostream>

// Суть гипотезы:
// Возьмем любое натуральное число.
// Если оно четное - разделим его пополам, если нечетное - умножим на 3, прибавим 1 и разделим пополам.
// Повторим эти действия с вновь полученным числом.
// Гипотеза гласит, что независимо от выбора первого числа рано или поздно мы получим 1.

int main(){
  int number;
  std::cout<<"We're going to proowe tge Siracus hypothesis"<<std::endl;
  std::cin>>number;
  if (number>0){
    while (number != 1){
      if (number %2 == 0){
        number = number/2;
      }
      else{
        number = ((number*3)+1)/2;
      }
      std::cout<<number<<std::endl;
    }
    std::cout<<"Теория была подтверждена";
  }
  else{
    return 0;
  }
  return 0;
}