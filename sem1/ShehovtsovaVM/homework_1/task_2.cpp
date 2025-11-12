#include <iostream>

float calculateTrapezoidArea(float a, float b, float h) {
	return 0.5 * (a + b) * h;
}

int main()
{
	float a, b, c;
	std::cin >> a >> b >> c;
	std::cout << calculateTrapezoidArea(a, b, c);
}
