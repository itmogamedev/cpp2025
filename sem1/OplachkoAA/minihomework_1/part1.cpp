#include <iostream>

void Vsqr(int side1){
    std::cout << "Площадь = " << side1 * side1 << std::endl;
}
int main(){
    int side1;
    std::cout << "Введите сторону квадрата: ";
    std::cin >> side1;
    Vsqr(side1);
    return 0;
}