#include <iostream>
using namespace std;

double calculateTrapezoidArea(double base_a, double base_b, double height) {
    return (base_a + base_b) / 2 * height;
}

int main() {
    double base_a, base_b, height;
    cout << "Введите основание A: ";
    cin >> base_a;
    cout << "Введите основание B: ";
    cin >> base_b;
    cout << "Введите высоту: ";
    cin >> height;
    cout << "Площадь трапеции = " << calculateTrapezoidArea(base_a, base_b, height) << endl;
    return 0;
}
