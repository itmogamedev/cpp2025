#include <iostream>

void Vtrap(int osn1,int osn2, int h){
    std::cout << "Площадь = " << (((osn1 + osn2) * 0.5) * h) << std::endl;
}
int main(){
    int osn1;
    int osn2;
    int h;
    std::cout << "Введите большее основание трапеции: ";
    std::cin >> osn1;
    std::cout << "Введите меньшее основание трапеции: ";
    std::cin >> osn2;
    std::cout << "Введите высоту трапеции: ";
    std::cin >> h;
    Vtrap(osn1, osn2, h);
    return 0;
}