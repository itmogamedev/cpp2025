//#include <iostream>
//using namespace std;
//
//double getSquareArea() {
//    double side;
//    cout << "Write a side of square: ";
//    cin >> side;
//    return side * side;
//}
//
//int main() {
//    double area = getSquareArea();
//    cout << "Square of square (Lmao): " << area << endl;
//    return 0;
//}
#include <iostream>
using namespace std;

double parallelogramArea() {
    double base, height;

    cout << "Write the side of paralelograma: ";
    cin >> base;
    cout << "Write the side of height: ";
    cin >> height;

    return base * height;
}

int main() {
    double area = parallelogramArea();
    cout << "Square of paralelograma: " << area << endl;
    return 0;
}