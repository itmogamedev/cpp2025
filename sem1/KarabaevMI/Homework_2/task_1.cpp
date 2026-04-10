#include<iostream>
void toHex(int n){
    std::cout <<std::hex<<n<< std::endl; 
}
void toOct(int n){
    std::cout <<std::oct<<n<< std::endl; 
}
int main(){
    toHex(16);
    toOct(8);
    return 0;
}

