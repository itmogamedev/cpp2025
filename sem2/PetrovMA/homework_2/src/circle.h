#ifndef MINIHW_CIRCLE_H
#define MINIHW_CIRCLE_H
#include <cstdint>


#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/System/Vector2.hpp"

class Game;

struct Circle {
public:
  sf::CircleShape shape;
  int64_t spawn_time;
  float radius;
  sf::Vector2f center;


  Circle(sf::Vector2f center, float radius) : center(center), radius(radius) {
    shape = sf::CircleShape(radius);
    shape.setOrigin({radius, radius});
    shape.setPosition(center);
    shape.setFillColor(sf::Color::White);
  }

  bool frameTick(Game *game);
  bool wasClicked(sf::Vector2i mousePos) const {
    return static_cast<sf::Vector2f>(mousePos - static_cast<sf::Vector2i>(center)).length() < radius;
  }
};

#endif // MINIHW_CIRCLE_H
