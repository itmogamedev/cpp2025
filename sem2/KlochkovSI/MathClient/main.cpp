#include <iostream>

#include "MathLibrary.h"
#include "vec3_demo.h"

int main() {
  Vec3 a(1.0f, 2.0f, 3.0f);
  Vec3 b(4.0f, 5.0f, 6.0f);
  printVectorOperations(a, b);
  return 0;
}
