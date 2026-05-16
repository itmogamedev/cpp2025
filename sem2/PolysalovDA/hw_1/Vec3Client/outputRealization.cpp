#define VEC3DLL_IMPORT
#include <conio.h>

#include <iostream>

#include "vec3.h"

void runVec3Demo() {
  Vec3 v1(1.0f, 2.0f, 3.0f);
  Vec3 v2(4.0f, 5.0f, 6.0f);

  std::cout << "V1: " << v1 << '\n';
  std::cout << "V2: " << v2 << '\n';
  std::cout << "V1 + V2: " << v2 + v1 << '\n';
  std::cout << "V2 - V1: " << v2 - v1 << '\n';
  std::cout << "V1*2: " << v1 * 2 << '\n';
  std::cout << "2*V2" << 2 * v2 << '\n';
  std::cout << "v1*v2(scalar): " << v1.scalarMultiply(v2) << '\n';
  std::cout << "v1*v2(vector): " << v1.vectorMultiply(v2) << '\n';
  std::cout << "Length V1: " << v1.length() << '\n';
  std::cout << "Lenght V2: " << v2.length() << '\n';

  v1.normalize();
  v2.normalize();
  std::cout << "Normalized V1: " << v1 << '\n';
  std::cout << "Normalized V2: " << v2 << '\n';

  std::cout << "\nPress any key to quit...";
  _getch();
}
