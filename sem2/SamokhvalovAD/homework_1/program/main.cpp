#include <iostream>

#include "vec3.h"


int main() {
    Vec3 vec1(1, 2, 3);
    Vec3 vec2(4, 5, 6);

    std::cout << "vec1: " << vec1 << std::endl;
    std::cout << "vec2: " << vec2 << std::endl;

    Vec3 sum = vec1 + vec2;
    std::cout << "vec1 + vec2: " << sum << std::endl;

    Vec3 diff = vec1 - vec2;
    std::cout << "vec1 - vec2: " << diff << std::endl;

    Vec3 scalarV = vec1 * vec2;
    std::cout << "vec1 * vec2 (scalar product): " << scalarV << std::endl;

    double scalar = 2.0;
    Vec3 scaledVec = vec1.scalar(scalar);
    std::cout << "vec1 * " << scalar << ": " << scaledVec << std::endl;

    Vec3 crossProduct = vec1.vec(vec2);
    std::cout << "vec1 x vec2 (cross product): " << crossProduct << std::endl;

    Vec3 normalizedVec = vec1.norm();
    std::cout << "Normalized vec1: " << normalizedVec << std::endl;

    double vectorLength = vec1.length();
    std::cout << "Length of vec1: " << vectorLength << std::endl;

    return 0;
}