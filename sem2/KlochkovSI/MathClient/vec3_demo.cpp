#include "vec3_demo.h"

#include <iostream>

void printVectorOperations(const Vec3& a, const Vec3& b) {
  std::cout << "Vector a: " << a << std::endl;
  std::cout << "Vector b: " << b << std::endl;
  std::cout << std::endl;

  std::cout << "=== Functions ===" << std::endl;
  std::cout << "add(a, b):             " << add(a, b) << std::endl;
  std::cout << "subtract(a, b):        " << subtract(a, b) << std::endl;
  std::cout << "multiplyByScalar(a, 2):" << multiplyByScalar(a, 2.0f)
            << std::endl;
  std::cout << "dotProduct(a, b):      " << dotProduct(a, b) << std::endl;
  std::cout << "crossProduct(a, b):    " << crossProduct(a, b) << std::endl;
  std::cout << "length(a):             " << length(a) << std::endl;
  std::cout << "normalize(a):          " << normalize(a) << std::endl;
  std::cout << std::endl;

  std::cout << "=== Operators ===" << std::endl;
  std::cout << "a + b:  " << (a + b) << std::endl;
  std::cout << "a - b:  " << (a - b) << std::endl;
  std::cout << "a * 3:  " << (a * 3.0f) << std::endl;
}
