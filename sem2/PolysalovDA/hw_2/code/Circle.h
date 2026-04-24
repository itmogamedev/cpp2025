#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <random>
#include <vector>

#include "Constants.h"

class Circle : public sf::Drawable {
 private:
  sf::CircleShape shape;
  sf::Vector2f position;
  sf::Vector2f velocity;
  float radius;
  bool active;

 public:
  Circle(float radius = CIRCLE_RADIUS);
  void setRandomPosition(const sf::Vector2u& window_size);
  void setRandomVelocity();
  void setPosition(const sf::Vector2f& pos);
  bool isOverlapping(const Circle& other) const;
  sf::Vector2f getPosition() const { return position; }
  float getRadius() const { return radius; }
  bool containsPoint(const sf::Vector2i& point) const;
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
  bool isActive() const { return active; }
  void setActive(bool act) { active = act; }
  void update(float delta_time, const sf::Vector2u& window_size);
};