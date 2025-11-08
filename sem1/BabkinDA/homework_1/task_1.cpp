#include <iostream>

float squere(float a){
    return a*a;
}

int main(){
    float a;
    std::cout << "Введите сторону квадрата: ";
    std::cin >> a;
    std::cout << "Площадь равна: " << squere(a) << std::endl;
}