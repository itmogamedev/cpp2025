#pragma once

#include <SFML/Graphics.hpp>

class Player final {
 public:
  void setup(const sf::Texture& texture);
  void reset();
  void move(float direction, float time);
  void update(float time);
  void draw(sf::RenderWindow& window) const;
  sf::FloatRect bounds() const;
  sf::Vector2f shotPoint() const;
  void blink();
  bool canBeHit() const;

 private:
  sf::RectangleShape shape;
  float blink_left = 0.0f;
};
