#pragma once

#include <SFML/Graphics.hpp>
#include <random>
#include <utility>

class Utility {
 public:
  static int getRandomInt(int min, int max);
  static sf::Vector2f newCirclePosition(int* _past,
                                        std::pair<int, int>* coordinates);
};
