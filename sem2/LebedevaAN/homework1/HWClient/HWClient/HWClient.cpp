#include "task_1.h"

int main() {
  Vec3 a = Vec3(1, 2, 3);
  Vec3 b = Vec3(-1, 3, 0);
  double c = 2.5;
  std::cout << a << "\n";
  std::cout << a + b << "\n";
  std::cout << a - b << "\n";
  std::cout << a * c << "\n";
  std::cout << a.dotProduct(b) << "\n";
  std::cout << a.crossProduct(b) << "\n";
  std::cout << a.len() << "\n";
  std::cout << a.getUnit() << "\n";
}