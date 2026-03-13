#define VEC3DLL_IMPORT  // для потребителя
#include "vec3.h"
#include <iostream>
#include <conio.h>  // для _getch()

int main() {
    Vec3 v(1.0f, 2.0f, 3.0f);
    std::cout << "Vector: " << v << std::endl;
    std::cout << "Length: " << v.length() << std::endl;

    Vec3 v2 = v.normalized();
    std::cout << "Normalized: " << v2 << std::endl;

    std::cout << "\nНажмите любую клавишу для выхода...";
    _getch();  // ждет нажатия любой клавиши
    return 0;
}