#include <iostream>

void trapezoid_area(int osn1,int osn2, int h){
  std::cout << "Площадь = " << (((osn1 + osn2) * 0.5) * h) << std::endl;
}

int main(){
  int long_base;
  int short_base;
  int height;
  std::cout << "Введите большее основание трапеции: ";
  std::cin >> long_base;
  std::cout << "Введите меньшее основание трапеции: ";
  std::cin >> short_base;
  std::cout << "Введите высоту трапеции: ";
  std::cin >> height;
  trapezoid_area(long_base, short_base, height);
  return 0;
}