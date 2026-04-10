#include <iostream>

float trapeze(float base_a, float base_b, float height) {
  return 0.5 * (base_a + base_b) * height;
}

int main() {
  setlocale(LC_ALL, "Russian");

  std::cout << "Ââåäèòå äëèíû îñíîâàíèé òðàïåöèè è âûñîòó ñîîòâåòñòâåííî "
               "(÷åðåç Enter): ";

  int base_a, base_b, height;
  std::cin >> base_a >> base_b >> height;

  float res;
  res = trapeze(base_a, base_b, height);
  std::cout << "Ïëîùàäü òðàïåöèè: " << res;

  return 0;
}
