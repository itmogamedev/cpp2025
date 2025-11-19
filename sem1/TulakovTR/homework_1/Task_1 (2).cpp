#include<iostream>
void main()
{
  setlocale(LC_ALL, "ru");
  float a, b, h;
  float s;
  cout << "Введите числа" << endl;
  cin >> a >> b >> h;
  s = ((a + b) / 2) * h;
  cout << "Площадь равна=" << s << endl;
}