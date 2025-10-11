#include<iostream>

double AreaOfSquare(double SideSize) {
	return SideSize * SideSize;
}

double AreaOfTrapezoid(double height, double base1,double base2) {
	return (base1+base2)/2 * height;
}

int main() {
	setlocale(LC_ALL, "rus");
	double squareSide, TrapDownSide, TrapTopSide, TrapHeight;
	std::cout << "¬ведите сторону квадрата:";
	std::cin >> squareSide;
	std::cout << "ѕлощадь квадрата: " << AreaOfSquare(squareSide);
	std::cout << "\n¬ведите верхнее основание тарапеции:";
	std::cin >> TrapTopSide;
	std::cout << "¬ведите нижнее основание трапеции:";
	std::cin >> TrapDownSide;
	std::cout << "¬ведите высоту трапеции:";
	std::cin >> TrapHeight;
	std::cout <<"ѕлощадь трапеции: " << AreaOfTrapezoid(TrapTopSide, TrapDownSide, TrapHeight);
	return 0;
}