#include <iostream>

#include "MathLibrary.h"

using namespace std;
using namespace MathLibrary;

int main() {
  setlocale(LC_ALL, "Russian");

  cout << "=== Тестирование ===\n";

  Vec3 v1(1, 2, 3);
  Vec3 v2(4, 5, 6);

  cout << "v1 + v2 = " << (v1 + v2) << endl;

  cin.get();
  return 0;
}
