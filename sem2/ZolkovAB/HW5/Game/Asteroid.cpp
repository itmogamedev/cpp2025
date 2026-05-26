#include "Asteroid.h"

Asteroid::Asteroid(float posX, float speed) {
  shape.setSize(sf::Vector2f(40.f, 40.f));
  shape.setFillColor(sf::Color::Red);
  shape.setPosition(sf::Vector2f(posX, -40.f));
  movementSpeed = speed;
}

void Asteroid::update() { shape.move(sf::Vector2f(0.f, movementSpeed)); }

void Asteroid::render(sf::RenderTarget& target) const { target.draw(shape); }

sf::FloatRect Asteroid::getBounds() const { return shape.getGlobalBounds(); }

float Asteroid::getPositionY() const { return shape.getPosition().y; }