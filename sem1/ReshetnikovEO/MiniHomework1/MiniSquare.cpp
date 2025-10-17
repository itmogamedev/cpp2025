#include <iostream>
using namespace std;

int square(int a) {
    return a * a;
}

int main() {
    int square_area;
    cout << "Please, type number for area of the square" << endl;
    cin >> square_area;
    cout << "Square area = " << square(square_area) << endl;
    return 0;
}