#include <iostream>
#include "../Mathlibrary/Vec3.h"

int main()
{
    Vec3 a(1, 2, 3);
    Vec3 b(4, 5, 6);

    Vec3 sum = a + b;
    Vec3 sub = a - b;
    Vec3 mul = a * 2;

    std::cout << "a + b = " << sum << std::endl;
    std::cout << "a - b = " << sub << std::endl;
    std::cout << "a * 2 = " << mul << std::endl;

    std::cout << "Dot = " << dot(a, b) << std::endl;

    Vec3 cr = cross(a, b);
    std::cout << "Cross = " << cr << std::endl;

    std::cout << "Length = " << length(a) << std::endl;

    Vec3 n = normalize(a);
    std::cout << "Normalize = " << n << std::endl;

    return 0;
}