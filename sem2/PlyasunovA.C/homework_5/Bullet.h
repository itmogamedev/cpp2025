#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>

class Bullet {
 public:
  explicit Bullet(const sf::Vector2f& position);
  void update(sf::Time delta_time);
  void draw(sf::RenderWindow& window);
  bool isActive() const;
  sf::FloatRect getBounds() const;

 private:
  sf::RectangleShape shape;
  sf::Vector2f velocity;
  bool active;
  static constexpr float kSpeed = -400.f;
  static constexpr float kWidth = 4.f;
  static constexpr float kHeight = 10.f;
};

#endif
