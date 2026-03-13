#include <iostream>
#include <MathLibrary.h>

int main() { 
	double x1, x2, y1, y2, z1, z2;

  std::cout << "The first vector x, y, z: " << std::endl;
  std::cin >> x1 >> y1 >> z1;
  std::cout << "\nThe second vector x, y, z: " << std::endl;
  std::cin >> x2 >> y2 >> z2;

  vector vec1(x1, y1, z1);
  vector vec2(x2, y2, z2);


  std::cout << "vector 1 = " << vec1 << std::endl;
  std::cout << "\nvector 2 = " << vec2 << std::endl;
  std::cout << "\nvector 1 + vector 2 " << (vec1 + vec2) << std::endl;
  std::cout << "\nvector 1 - vector 2 " << (vec1 - vec2) << std::endl;

  double scalarr;
  std::cout << "\nType scalar: " << std::endl;
  std::cin >> scalarr;
  std::cout << "\nvector 1 * scalar " << (vec1 * scalarr) << std::endl;
  std::cout << "\nscalar multiply " << (scalarMultiply(vec1, vec2)) << std::endl;
  std::cout << "\nvector multiply " << (vectorMultiply(vec1, vec2)) << std::endl;
  std::cout << "\nlength of the vectors: " << (length(vec1)) << ", " << (length(vec2)) << std::endl;
  std::cout << "\nnormalized vectors: " << (normalize(vec1)) << ", " << (normalize(vec2)) << std::endl;
}