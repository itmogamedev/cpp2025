#include <iostream>
using namespace std;

double calculateSquareArea(double side) {
    return side * side;
}

int main() {
    double side;
    cout << "Введите сторону квадрата: ";
    cin >> side;
    cout << "Площадь квадрата = " << calculateSquareArea(side) << endl;
    return 0;
}
