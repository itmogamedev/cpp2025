#include <iostream>
#include <string>

float square(float a) {
	return a * a;
}

int main() {

	setlocale(LC_ALL, "Russian");

	float a;
	std::cout << "¬ведите длину стороны квадрата: ";
	std::cin >> a;

	float res = square(a);
	std::cout << "ѕлощадь квадрата: " << res << std::endl;

	return 0;
}