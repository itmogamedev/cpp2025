#include <iostream>
using namespace std;

int main() {
    double a, b, h;
    cout << "Введите длину первого основания: ";
    cin >> a;
    cout << "Введите длину второго основания: ";
    cin >> b;
    cout << "Введите высоту трапеции: ";
    cin >> h;
    double area = (a + b) * h / 2.0;
    cout << "Площадь трапеции: " << area;
}
