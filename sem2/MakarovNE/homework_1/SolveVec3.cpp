
#include <iostream>

#include "..\MathVec3\Vec3.h"

void main2();

int main() {
  main2();
  return 0;
}

void main2() {
  Vec3 vecA(1.0f, 2.0f, 3.0f);
  Vec3 vecB(4.0f, 5.0f, 6.0f);

  std::cout << "Vector A: " << vecA << std::endl;
  std::cout << "Vector B: " << vecB << std::endl;
  std::cout << "A + B: " << vecA + vecB << std::endl;
  std::cout << "A * 2.0: " << vecA * 2.0f << std::endl;
  std::cout << "Scolar A on B: " << vecA.skProduct(vecB) << std::endl;
  std::cout << "Vec_Proi A on B: " << vecA.vcProduct(vecB) << std::endl;
  std::cout << "Length A: " << vecA.length() << std::endl;
  std::cout << "Normalization A: " << vecA.normalize() << std::endl;
}
