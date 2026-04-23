#pragma once
#include "SFML/System/Vector2.hpp"
#include "float2.h"

class Circle {
 public:
  int radius;
  sf::Vector2<float> position;
  sf::Vector2<float> velocity;
  Circle(int radius, sf::Vector2<float> position,
         sf::Vector2<float> angularSpeed)
      : radius(radius), position(position), velocity(angularSpeed) {}
};
