#include <iostream>
#include "libs/mathlib.h"

int main() {
    Vec3 v1 = { 1, 2, 3 };
    Vec3 v2 = { 3, 2, 1 };
    std::cout << v1 << " " << v2 << std::endl;
    std::cout << v1 * v2 << std::endl;
    std::cout << v1 + v2 << std::endl;
    std::cout << v1 - v2 << std::endl;
    std::cout << cross(v1, v2) << std::endl;
    std::cout << v1.length() << std::endl;
    std::cout << v1.normalize() << std::endl;
    std::cout << v1.normalize().length() << std::endl;
    return 0;
}