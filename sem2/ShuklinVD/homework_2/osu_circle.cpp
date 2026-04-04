#include "osu_circle.h"

OsuCircle::OsuCircle(float x, float y, sf::Vector2f speed) {
  circle_speed = speed;
  shape.setFillColor(sf::Color::Red);
  shape.setRadius(RADIUS_OF_CIRCLE);
  shape.setPosition(sf::Vector2f(x, y));
}

sf::FloatRect OsuCircle::getBounds() { return shape.getGlobalBounds(); }

sf::Vector2f OsuCircle::getPosition() { return shape.getPosition(); }

void OsuCircle::moveCircle() {
  shape.move(circle_speed * SPEED_MODIFICATOR);

  sf::Vector2f position = shape.getPosition();

  if (position.x < 0 || position.x + DIAMETR_OF_CIRCLE > WIDTH_OF_WINDOW) {
    circle_speed.x = -circle_speed.x;
  }
  if (position.y < 0 || position.y + DIAMETR_OF_CIRCLE > HEIGHT_OF_WINDOW) {
    circle_speed.y = -circle_speed.y;
  }
}

sf::CircleShape OsuCircle::getShape() { return shape; }
