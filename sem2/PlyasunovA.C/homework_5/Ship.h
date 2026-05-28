#ifndef SHIP_H
#define SHIP_H

#include <SFML/Graphics.hpp>

class Ship {
 public:
  Ship();
  void update(sf::Time delta_time);
  void draw(sf::RenderWindow& window);
  void handleInput();
  sf::FloatRect getBounds() const;
  void resetPosition();

 private:
  sf::RectangleShape shape;
  sf::Vector2f velocity;
  float speed;
  static constexpr float kLeftBound = 20.f;
  static constexpr float kRightBound = 780.f;
  static constexpr float kShipWidth = 40.f;
  static constexpr float kShipHeight = 30.f;
};

#endif
