#ifndef OSU_CIRCLE_H
#define OSU_CIRCLE_H

#include <SFML/Graphics.hpp>

#include "Constants.h"

class OsuCircle {
 private:
  sf::CircleShape shape;
  sf::Vector2f circle_speed;

 public:
  OsuCircle(float x, float y, sf::Vector2f speed);
  sf::FloatRect getBounds();
  sf::Vector2f getPosition();
  void moveCircle();
  sf::CircleShape getShape();
};

#endif
