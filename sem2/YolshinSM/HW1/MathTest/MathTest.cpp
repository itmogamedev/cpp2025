#include <iostream>

#include "vector.h"

int main() {
  Vec3 v1(1, 2, 3);
  Vec3 v2(4, 5, 6);

  std::cout << "v1 + v2 = " << v1 + v2 << std::endl;
  std::cout << "len v1 = " << v1.length() << std::endl;
  std::cout << "v1 * v2" << v1.cross(v2) << std::endl;
  return 0;
}
