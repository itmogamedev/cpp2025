#pragma once

#include <SFML/Graphics.hpp>
#include <random>
#include <utility>
#include "constants.h"

class Utility {
 public:
  static float getRandomFloat(int min, int max);
  static sf::Vector2f newCirclePosition();
};
