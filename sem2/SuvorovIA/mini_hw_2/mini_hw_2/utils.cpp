#include "utils.h"

int Utility::getRandomInt(int min, int max) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(min, max);
  return dis(gen);
}
sf::Vector2f Utility::newCirclePosition(int* _past,
                                        std::pair<int, int>* coordinates) {
  int ind = getRandomInt(0, 4);
  if (*_past != ind) {
    *_past = ind;
    return sf::Vector2f(coordinates[ind].first, coordinates[ind].second);
  }
  return newCirclePosition(_past, coordinates);
}
