#include "Utils.h"

namespace Utils {
int randomInt(int min, int max) {
  std::uniform_int_distribution<int> dist(min, max);
  return dist(randomEngine);
}

float randomFloat(float min, float max) {
  std::uniform_real_distribution<float> dist(min, max);
  return dist(randomEngine);
}
}  // namespace Utils
