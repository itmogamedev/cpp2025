#include <iostream>

float countAreaTrapezoid(float larger_baze, float smaller_baze, float height) {
  if (larger_baze > 0 && smaller_baze > 0 && height > 0) {
    return (((larger_baze + smaller_baze) / 2) * height);
  } else {
    return -1;
  }
}

int main() { std::cout << countAreaTrapezoid(5.5f, 2.0f, 4.0f); }
