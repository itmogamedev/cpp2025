#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

#include "Utils.h"

class CircleTarget {
 public:
  CircleTarget(float x, float y, float radius, const sf::Color& color,
               float windowWidth, float windowHeight);

  void draw(sf::RenderWindow& window) const;
  void move(sf::Time deltaTime);
  sf::Vector2f getPosition() const;
  float getRadius() const;

 private:
  sf::CircleShape shape_;
  sf::Vector2f velocity_;
  float window_width_;
  float window_height_;
};
