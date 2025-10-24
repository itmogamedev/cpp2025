#include <iostream>

int square(int side_square)
{
    return side_square*side_square;
}

int trapezoid(int base_upper, int base_lower, int height)
{
    return ((base_upper+base_lower)/2)*height;
}

int main()
{
    int square_side;
    int upper_base;
    int lower_base;
    int height;
    std::cout<<"Введите сторону квадрата:";
    std::cin>>square_side;
    std::cout<<"Площадь квадрата:";
    std::cout<<square(square_side)<<std::endl;
    std::cout<<"Введите 1 основание трапеции:";
    std::cin>>upper_base;
    std::cout<<"Введите 2 основание трапеции:";
    std::cin>>lower_base;
    std::cout<<"Введите высоту трапеции:";
    std::cin>>height;
    std::cout<<trapezoid(upper_base, lower_base, height);
    return 0;
}


