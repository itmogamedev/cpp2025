#include "asteroid.h"

#include "constants.h"

Asteroid::Asteroid(sf::Vector2f position, float radius, float asteroid_speed)
    : speed(asteroid_speed) {
  shape.setPointCount(9);
  shape.setRadius(radius);
  shape.setOrigin({radius, radius});
  shape.setPosition(position);
  shape.setFillColor(sf::Color(120, 125, 140));
  shape.setOutlineColor(sf::Color(210, 215, 225));
  shape.setOutlineThickness(2.0F);
}

void Asteroid::update(float delta_time) {
  shape.move({0.0F, speed * delta_time});
  shape.rotate(35.0F * delta_time);
}

void Asteroid::draw(sf::RenderWindow& window) const { window.draw(shape); }

bool Asteroid::isOutOfWindow() const {
  return shape.getPosition().y - shape.getRadius() >
         static_cast<float>(constants::kWindowHeight);
}

sf::FloatRect Asteroid::getBounds() const { return shape.getGlobalBounds(); }

sf::Vector2f Asteroid::getPosition() const { return shape.getPosition(); }

float Asteroid::getRadius() const { return shape.getRadius(); }
