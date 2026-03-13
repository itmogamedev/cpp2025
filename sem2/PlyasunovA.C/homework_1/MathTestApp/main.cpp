#include <iostream>
#include "vec3.h"

int main() {
    math::Vec3 v1(1, 2, 3), v2(4, 5, 6);

    std::cout << "v1+v2=" << v1 + v2 << " dot=" << math::dot(v1, v2)
        << " cross=" << math::cross(v1, v2)
        << " norm=" << math::normalize(v1) << std::endl;

    return 0;
}