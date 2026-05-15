#include <iostream>
#include <string>

#include "../Dll1/VecLib.h"

void demonstrateVec3Operations() {
  Vec3 v2(1.0, 2.0, 3.0);
  Vec3 v3(4.0, 5.0, 6.0);

  std::cout << "v2: ";
  funcForOut(std::cout, v2);
  std::cout << std::endl;
  std::cout << "v3: ";
  funcForOut(std::cout, v3);
  std::cout << std::endl;

  Vec3 sum = v2.Summator(v3);
  std::cout << "v2 + v3 = ";
  funcForOut(std::cout, sum);
  std::cout << std::endl;

  Vec3 diff = v2.Minusator(v3);
  std::cout << "v2 - v3 = ";
  funcForOut(std::cout, diff);
  std::cout << std::endl;

  double constValue = 2.5;
  Vec3 multiplied = v2.umnojatorConst(constValue);
  std::cout << "v2 * " << constValue << " = ";
  funcForOut(std::cout, multiplied);
  std::cout << std::endl;

  Vec3 multiplied2 = 3.0 * v2;
  std::cout << "3.0 * v2 = ";
  funcForOut(std::cout, multiplied2);
  std::cout << std::endl;

  double dot = v2.Scalyarnoe(v3);
  std::cout << "v2 · v3 = " << dot << std::endl;

  Vec3 cross = v2.Vectornoe(v3);
  std::cout << "v2 × v3 = ";
  funcForOut(std::cout, cross);
  std::cout << std::endl;

  double len = v2.length();
  std::cout << "|v2| = " << len << std::endl;
  std::cout << "|v3| = " << v3.length() << std::endl;

  Vec3 normalized = v2.normalizedVersion();
  std::cout << "v2 normalized = ";
  funcForOut(std::cout, normalized);
  std::cout << std::endl;
  std::cout << "normalized length: " << normalized.length() << std::endl;
}

int main() {
  demonstrateVec3Operations();
  return 0;
}
