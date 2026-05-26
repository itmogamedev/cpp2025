#ifndef ASTEROID_H_
#define ASTEROID_H_

#include <SFML/Graphics.hpp>

class Asteroid {
 public:
  Asteroid(sf::Vector2f position, float radius, float asteroid_speed);

  void update(float delta_time);
  void draw(sf::RenderWindow& window) const;

  bool isOutOfWindow() const;
  sf::FloatRect getBounds() const;
  sf::Vector2f getPosition() const;
  float getRadius() const;

 private:
  sf::CircleShape shape;
  float speed;
};

#endif  // ASTEROID_H_
