#include <iostream>
using namespace std;

int main() {
    int number;
    cout << "Введите число: ";
    cin >> number;

    cout << "Шестнадцатеричное: " << hex << number << endl;
    cout << dec;
    cout << "Восьмеричное: " << oct << number << endl;
    cout << dec;
    return 0;
}
