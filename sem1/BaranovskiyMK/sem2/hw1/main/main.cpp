#include <dll_lib.h>

#include <iostream>

int main(int argc, char **argv) {
    Vec3 vec3_a = (Vec3){1.0, 0.0, 0.0};
    Vec3 vec3_b = (Vec3){0.0, 1.0, 0.0};
    Vec3 vec3_c = (Vec3){0};


    vec3_c = vec3_a + vec3_b;
    float c = multyplay_v_v(&vec3_c, &vec3_c);
    std::cout << "\n" << c << "\n" << vec3_c << "\n";
    return 0;
}