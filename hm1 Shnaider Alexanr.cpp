#include <iostream>

int main() {
	char ans;
	float square;
	float high;
	float osn1;
	float osn2;
	setlocale(LC_ALL, "RU");
	std::cout << "выбери фигуру (s/t)"<<std::endl;
	std::cin >> ans;
	if (ans == 's') {
		std::cout << "укажите сторону квадрата" << std::endl;
		std::cin >> square;
		std::cout << "Площадь равна  "<< square*square;

	}
	if (ans == 't') {
		std::cout << "укажите высоту" << std::endl;
		std::cin >> high;
		std::cout << "укажите основание 1" << std::endl;
		std::cin >> osn1;
		std::cout << "укажите основание 2" << std::endl;
		std::cin >> osn2;
		std::cout << "Площадь равна  " << (osn1+osn2)/2 * high << std::endl;


	}
	std::cout << "Для закрытия программы нажмите любую клавишу и enter";
	char x;
	std::cin >> x;
}

