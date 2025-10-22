#include <iostream>
using namespace std;

double areaOfTrapezoid(double a, double b, double h) {
    return (a + b) * h / 2.0;
}

int main() {
    double a, b, h;
    
    cout << "Vvedite dliny pervogo ocnovania (a): ";
    cin >> a;
    cout << "Vvedite dliny vtorogo ocnovania (b): ";
    cin >> b;
    cout << "Vvedite visoty trapetshii (h): ";
    cin >> h;
    
    double result = areaOfTrapezoid(a, b, h);
    cout << "ploshad trapth: " << result << endl;
    
    return 0;
}