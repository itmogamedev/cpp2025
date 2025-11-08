#include <iostream>

float square(float side) { return side * side; }

int main() {
  setlocale(LC_ALL, "Russian");

  float side;
  std::cout << "Ââåäèòå äëèíó ñòîðîíû êâàäðàòà: ";
  std::cin >> side;

  float result = square(side);
  std::cout << "Ïëîùàäü êâàäðàòà: " << result;
}
