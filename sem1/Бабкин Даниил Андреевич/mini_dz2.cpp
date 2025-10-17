#include <iostream>
#include <string>

using namespace std;
int start = 1;

string decimalToHex (int decimal) {
    string hexChars = "0123456789ABCDEF";
    string hexResult;

    while (decimal > 0) {
        hexResult = hexChars[decimal % 16] + hexResult;
        decimal /= 16;
    }
    return hexResult.empty() ? "0" : hexResult;
}

string decimalToOct (int decimal) {
    string octChars = "01234567";
    string octResult;

    while (decimal > 0) {
        octResult = octChars[decimal % 8] + octResult;
        decimal /= 8;
    }
    return octResult.empty() ? "0" : octResult;
}
string decimalToOne (int decimal){
    while (decimal != 1) {
        if (decimal % 2 == 0){
            decimal /= 2;
            cout << decimal << endl;
        }
        else {
            decimal = decimal * 3 + 1;
            cout << decimal << endl;
        }
    }
    return "Из данного числа получился 1";
    
}

int main() {
    while (start == 1) {
        int choise;
        cout << "1. Перевод из 10-ой сис в 16-ую.\n2. Перевод из 10-ой в 8-ую.\n3. Гипотеза Сиракуз.\n4. Выйти.\n";
        cin >> choise;
        switch (choise) {
            case 1: {
                int decimal;
                cout << "Введите число: ";
                cin >> decimal;
                cout << decimalToHex(decimal) << endl;
                break;
            }
            case 2: {
                int decimal;
                cout << "Введите число: ";
                cin >> decimal;
                cout << decimalToOct(decimal) << endl;
                break;
            }
            case 3: {
                int decimal;
                cout << "Введите число: ";
                cin >> decimal;
                cout << decimalToOne(decimal) << endl;
                break;
            }
            case 4: {
                start = 0;
                break;
            }
        }
    }
}