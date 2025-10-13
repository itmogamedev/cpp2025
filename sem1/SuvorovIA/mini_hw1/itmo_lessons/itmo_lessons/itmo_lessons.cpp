#include <iostream>
using namespace std;

float Square() 
{
    int side = 0;

    cout << "Input your side: ";
    cin >> side;

    return side * side;
}
float Trapezoid()
{
    float side1 = 0;
    float side2 = 0;
    float height = 0;
    float area = 0;

    cout << "Input your 1 side: ";
    cin >> side1;

    cout << "Input your 2 side: ";
    cin >> side2;

    cout << "Input your height: ";
    cin >> height;

    area = (side1 + side2) / 2 * height;
    return area;
}

int main()
{
    cout << Square() << endl;
    cout << "" << endl; 
    cout << Trapezoid() << endl;
}