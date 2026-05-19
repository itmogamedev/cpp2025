#ifndef BULLET_H_
#define BULLET_H_

#include <SFML/Graphics.hpp>

class Bullet {
 public:
  explicit Bullet(sf::Vector2f position);

  void update(float delta_time);
  void draw(sf::RenderWindow& window) const;

  bool isOutOfWindow() const;
  sf::FloatRect getBounds() const;

 private:
  sf::CircleShape shape;
};

#endif  // BULLET_H_
