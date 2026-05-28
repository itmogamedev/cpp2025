#ifndef ASTEROID_H
#define ASTEROID_H

#include <SFML/Graphics.hpp>

class Asteroid {
 public:
  Asteroid(const sf::Vector2f& position, float base_speed);
  void update(sf::Time delta_time);
  void draw(sf::RenderWindow& window);
  sf::FloatRect getBounds() const;
  bool isOutOfBounds(float window_height) const;
  void setSize(float radius);

 private:
  sf::CircleShape shape;
  sf::Vector2f velocity;
};

#endif
