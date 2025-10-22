#include <iostream>
using namespace std;

int main() {
    int number;
    cout << "Chislo:";
    cin >> number;
    
    cout << "Vosmerichnoe:";
    int temp = number;
    
    if (temp == 0) {
        cout << "0";
    }
    
    if (temp > 0) {
        string octal = "";
        while (temp > 0) {
            int ostatok = temp % 8;
            octal = to_string(ostatok) + octal;
            temp = temp / 8;
        }
        cout << octal;
    }
    
    if (temp < 0) {
        temp = -temp;
        string octal = "";
        while (temp > 0) {
            int ostatok = temp % 8;
            octal = to_string(ostatok) + octal;
            temp = temp / 8;
        }
        cout << "-" << octal;
    }
    
    cout << endl;
    
    cout << "Shestnatherichnoe:";
    temp = number;
    
    if (temp == 0) {
        cout << "0";
    }
    
    if (temp > 0) {
        string hex = "";
        while (temp > 0) {
            int ostatok = temp % 16;
            char hexChar;
            if (ostatok < 10) {
                hexChar = '0' + ostatok;
            } else {
                hexChar = 'A' + (ostatok - 10);
            }
            hex = hexChar + hex;
            temp = temp / 16;
        }
        cout << hex;
    }
    
    if (temp < 0) {
        temp = -temp;
        string hex = "";
        while (temp > 0) {
            int ostatok = temp % 16;
            char hexChar;
            if (ostatok < 10) {
                hexChar = '0' + ostatok;
            } else {
                hexChar = 'A' + (ostatok - 10);
            }
            hex = hexChar + hex;
            temp = temp / 16;
        }
        cout << "-" << hex;
    }
    
    cout << endl;
    
    return 0;
}