#include <iostream>
using namespace std;
int squere(int a)
    {
        return a * a;
    }
float trap(int a, int b, int h){
    return ((a+b)/2)*h;
}

int q = 1;

int main(){
    while (q == 1){
        int p;
        cout << "1) Посчитать площадь квадрата.\n2) Посчитать площадь трапеции.\n3)Выйти.\n";
        cin >> p;
        switch (p){
            case 1:{
                int a;
                cout << "Введите сторону квадрата: ";
                cin >> a;
                cout << "Площадь квадрата равна: " << squere(a) << endl;
                break;
            }
            case 2:{
                int a,b,h;
                cout << "Введите длины оснований и высоту через пробел соответственно: ";
                cin >> a >> b >> h;
                cout << "Площадь трапеции равна: " << trap(a,b,h) << endl;
                break;
            }
            case 3:{
                q = 2;
                break;
            }
        }   
        
    }
}