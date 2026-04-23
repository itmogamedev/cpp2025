#include "Object.h"
#include "Constants.h"
#include <SFML/Graphics.hpp>

Object::Object(int size, sf::Vector2f circlePos) : size(size), circlePos(circlePos) {
  shape.setOrigin(size, size);
  shape.setRadius(size);
  shape.setFillColor(sf::Color::Magenta);
  shape.setPosition(circlePos);
  speed = sf::Vector2f(SPEED, SPEED);
}

void Object::updatePos(float frame) {
  circlePos += speed * frame;

  if (circlePos.x < size) {
    circlePos.x = size;
    speed.x *= SPEED_REVERSE;
  } else if (circlePos.x > (WINDOW_WIDTH - size)) {
    circlePos.x = WINDOW_WIDTH - size;
    speed.x *= SPEED_REVERSE;
  }

  if (circlePos.y < size) {
    circlePos.y = size;
    speed.y *= SPEED_REVERSE;
  } else if ((WINDOW_HEIGHT - size) < circlePos.y) {
    circlePos.y = WINDOW_HEIGHT - size;
    speed.y *= SPEED_REVERSE;
  }
  shape.setPosition(circlePos);
}

bool Object::nearCursor(sf::Vector2f& mousePos) {
  auto distanceX = circlePos.x  - mousePos.x;
  auto distanceY = circlePos.y - mousePos.y;
  return ((distanceX * distanceX + distanceY * distanceY) <= (size * size));
}

void Object::setPos(sf::Vector2f newCirclePos) { 
  circlePos = newCirclePos;
  shape.setPosition(circlePos); 
}

void Object::setSpeed(sf::Vector2f newSpeed) { speed = newSpeed; }

void Object::draw(sf::RenderWindow& window) { window.draw(shape); }