#include <iostream>

int numChet(int number){
    int newNumber;
    newNumber = number/2;
    std::cout << newNumber << " ";
    return newNumber;
}

int numNeChet(int number){
    int newNumber;
    newNumber = ((number*3)+1)/2;
    std::cout << newNumber << " ";
    return newNumber;
}

int main(){
    int number;
    std::cout << "Введите число: ";
    std::cin >> number;
    std::cout << "Последовательность: " << number << " ";
    while (number != 1){
        
        if (number%2==0){
            number = numChet(number);
        }
        else{
            number = numNeChet(number);
        }
        
    }
    std::cout << std::endl;
}