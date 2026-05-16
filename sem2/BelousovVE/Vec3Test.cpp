#include <iostream>
#include "Vec3.h"

int main()
{
	// preparations and showcase -> getLength; getNormalized
	Vec3 vec01 = Vec3(2, 2, 8);

	std::cout << "length\n";
	std::cout << vec01.getLength() << "\n\n";

	std::cout << "normalization\n";
	std::cout << vec01.getNormalized() << "\n\n";

	// addition
	Vec3 vec02 = Vec3(7, 7, 7);

	std::cout << "addition\n";
	std::cout << vec01 + vec02  << "\n\n";

	// substruction
	std::cout << "substruction\n";
	std::cout << vec01 - vec02 << "\n\n";


	// scalar left-right multiplication
	double scalar = 11;

	std::cout << "scalar left-right multiplication\n";
	std::cout << vec01 * scalar << " " << scalar * vec01 << "\n\n";

	// scalar vector multiplication
	std::cout << "scalar vector multiplication\n";
	std::cout << vec01 * vec02 << "\n\n";

	// vector multiplication
	std::cout << "scalar multiplication\n";
	std::cout << vec01 % vec02 << "\n\n";
}
