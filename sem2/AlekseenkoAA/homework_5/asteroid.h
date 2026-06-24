#pragma once

#include <SFML/Graphics.hpp>

#include "randomsystem.h"

class Asteroid final {
 public:
  explicit Asteroid(const sf::Texture& texture);
  void respawn(RandomSystem& random, float base_speed, bool above_window);
  void update(float time);
  void draw(sf::RenderWindow& window) const;
  sf::FloatRect bounds() const;

 private:
  sf::RectangleShape shape;
  float speed = 0.0f;
};
