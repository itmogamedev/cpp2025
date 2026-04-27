#pragma once

#include <SFML/Graphics.hpp>

#include "RandomGenerator.h"

class MovingCircle {
 public:
  MovingCircle(float x, float y, sf::Vector2f velocity, sf::Vector2f field_size,
               float radius = 30.f);

  sf::Vector2f getPosition() const;
  void setPosition(const sf::Vector2f& pos);

  void setVelocity(const sf::Vector2f& vel);
  sf::Vector2f getVelocity() const;

  const sf::Shape& getShape() const;

  void move(float dt);
  bool hit(const sf::Vector2f& point) const;
  bool teleportIfHit(const sf::Vector2f& point, RandomGenerator& randGen);

 private:
  sf::CircleShape shape;
  sf::Vector2f velocity;
  sf::Vector2f field_size;
};
