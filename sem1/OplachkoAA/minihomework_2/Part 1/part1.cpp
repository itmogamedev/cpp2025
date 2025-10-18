#include <iostream>
void iz10v16(int a){
    std::cout << std::hex << a << std::endl; 
}
void iz10v8(int b){
    std::cout << std::oct << b << std::endl;
}
int main(){
    int a;
    int b;
    std::cout << "Введите десятичное число для перевода в шестнадцатиричную: ";
    std::cin >> a;
    iz10v16(a);
    std::cout << "Введите десятичное число для перевода в восьмиричную: ";
    std::cin >> b;
    iz10v8(b);
    return 0;
}