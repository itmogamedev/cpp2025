#pragma once

#include <SFML/Graphics.hpp>

class Projectile final {
 public:
  explicit Projectile(sf::Vector2f point);
  void update(float time);
  void draw(sf::RenderWindow& window) const;
  sf::FloatRect bounds() const;
  bool isActive() const;
  void stop();

 private:
  sf::RectangleShape shape;
  bool active = true;
};
