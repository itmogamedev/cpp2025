#include <iostream>

float trap(float a, float b, float h){
    return (a+b)/2 * h;
}

int main(){
    float a, b, h;
    std::cout << "Введите основания и высоту через пробел: ";
    std::cin >> a >> b >> h;
    std::cout << "Площадь равна: " << trap(a, b, h) << std::endl;
}