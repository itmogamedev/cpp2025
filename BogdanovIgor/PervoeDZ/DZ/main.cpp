#include<iostream>

double AreaOfSquare(float SideSize) {
	return SideSize * SideSize;
}

double AreaOfTrapezoid(float height, float base1,float base2) {
	return (base1+base2)/2 * height;
}

int main() {

	std::cout << AreaOfTrapezoid(5,3,2);
	return 0;
}