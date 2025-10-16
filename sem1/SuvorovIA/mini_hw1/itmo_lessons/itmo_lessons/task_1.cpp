#include <iostream>
using namespace std;

float square_area()
{
	int side = 0;

	cout << "Input your side: ";
	cin >> side;

	return side * side;
}

int main()
{
	cout << square_area() << endl;
}