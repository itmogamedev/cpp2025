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
	std::cout << "������� ������� ��������:";
	std::cin >> squareSide;
	std::cout << "������� ��������: " << AreaOfSquare(squareSide);
	std::cout << "\n������� ������� ��������� ���������:";
	std::cin >> TrapTopSide;
	std::cout << "������� ������ ��������� ��������:";
	std::cin >> TrapDownSide;
	std::cout << "������� ������ ��������:";
	std::cin >> TrapHeight;
	std::cout <<"������� ��������: " << AreaOfTrapezoid(TrapTopSide, TrapDownSide, TrapHeight);
	return 0;
}