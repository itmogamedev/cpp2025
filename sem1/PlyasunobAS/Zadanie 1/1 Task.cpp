#include <iostream>
using namespace std;

double squareArea(double side) {
    return side * side;
}

int main() {
    double side = 5.0;
    
    cout << "Площадь квадрата: " << squareArea(side);
    
    return 0;
}