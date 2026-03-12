#include <iostream>
#include "vect.h"

int main() {
    Vec3 v1(1, 2, 3);
    Vec3 v2(4, 5, 6);
    double scalar = 2.5;

    std::cout << "v1 = " << v1 << std::endl;
    std::cout << "v2 = " << v2 << std::endl;
    std::cout << "scalar = " << scalar << std::endl << std::endl;

    std::cout << "vecSum(v1, v2) = " << vecSum(v1, v2) << std::endl;
    std::cout << "vecSubtraction(v1, v2) = " << vecSubtraction(v1, v2) << std::endl;
    std::cout << "vecScalMult(v1, scalar) = " << vecScalMult(v1, scalar) << std::endl;
    std::cout << "vecScalMult(scalar, v1) = " << vecScalMult(scalar, v1) << std::endl;
    std::cout << "scalMult(v1, v2) = " << scalMult(v1, v2) << std::endl;
    std::cout << "vecMult(v1, v2) = " << vecMult(v1, v2) << std::endl;
    std::cout << "lenVec(v1) = " << lenVec(v1) << std::endl;
    std::cout << "normVec(v1) = " << normVec(v1) << std::endl;
    std::cout << "lenVec(normVec(v1)) = " << lenVec(normVec(v1)) << std::endl;

    Vec3 zero(0, 0, 0);
    std::cout << "normVec(zero) = " << normVec(zero) << std::endl;

    return 0;
}