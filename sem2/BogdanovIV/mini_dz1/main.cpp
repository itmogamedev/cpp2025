

#include <iostream>

#include "Vec3.h"

int main() {
  Vec3 vec1(0, 0, 0), vec2(1, 2, 3), vec3(1, 0, 0);

  std::cout << vec1 << vec2 << vec3 << '\n';

  Vec3 vec4 = vec2 - vec3;

  std::cout << vec4 << '\n';

  Vec3 vec5 = vec2 * vec1;

  std::cout << vec5 << '\n';

  Vec3 vec6 = cross(vec4, vec2);

  std::cout << vec6;

  return 0;
}
