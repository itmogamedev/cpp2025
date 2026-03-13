#include <iostream>

#include "vec3.h"

void test() {
	Vec3 a(1, 0, 1);
	Vec3 b(2, 0, -6);

	std::cout << a + b << std::endl;
	std::cout << a * 5 << std::endl;
	std::cout << dot_prod(a, b) << std::endl;
	std::cout << vector_product(b, a) << std::endl;
	std::cout << vector_product(a, b) << std::endl;
}

int main() {
	test();
}
