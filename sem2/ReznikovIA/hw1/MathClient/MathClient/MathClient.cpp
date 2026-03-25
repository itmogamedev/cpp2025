// MathClient.cpp : Client app for MathLibrary DLL.
// #include "pch.h" Uncomment for Visual Studio 2017 and earlier
#include <iostream>

#include "Vec3.h"

int main() {
  Vec3 v1 = Vec3(2.0f, 1.0f, 1.0f);
  Vec3 v2 = Vec3(0.0f, 1.0f, 1.0f);
  std::cout << "V1: " << v1 << std::endl;
  std::cout << "V2: " << v2 << std::endl;
  std::cout << "---" << std::endl;
  std::cout << "Sum: " << v1 + v2 << std::endl;
  std::cout << "Difference: " << v1 - v2 << std::endl;
  std::cout << "Scalar(2): " << v1 * 2.0f << std::endl;
  std::cout << "Dot: " << v1.dot(v2) << std::endl;
  std::cout << "Cross: " << v1.cross(v2) << std::endl;
  std::cout << "Length: " << v1.length() << std::endl;
  std::cout << "Normalized: " << v1.normalized() << std::endl;
  ;
}
