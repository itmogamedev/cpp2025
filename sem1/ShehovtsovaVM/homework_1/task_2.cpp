#include <iostream>
using namespace std;

float calculateTrapezoidArea(float a, float b, float h) {
	return 0.5 * (a + b) * h;
}

int main()
{
	float a, b, c;
	cin >> a >> b >> c;
	cout << calculateTrapezoidArea(a);
}
