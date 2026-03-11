#include "Vec3.h"

#include <iostream>
#include "Vec3.h"

int main()
{
    Vec3 a(1, 2, 3);
    Vec3 b(4, 5, 6);

    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;

    std::cout << "a + b = " << a + b << std::endl;
    std::cout << "a - b = " << a - b << std::endl;
    std::cout << "a * 2 = " << a * 2 << std::endl;

    std::cout << "dot(a,b) = " << a.dot(b) << std::endl;
    std::cout << "cross(a,b) = " << a.cross(b) << std::endl;

    std::cout << "length(a) = " << a.length() << std::endl;
    std::cout << "normalize(a) = " << a.normalize() << std::endl;
}