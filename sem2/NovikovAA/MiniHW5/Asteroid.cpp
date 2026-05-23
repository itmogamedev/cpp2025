#include "Asteroid.h"

Asteroid::Asteroid(float x, float spd) {
  shape.setRadius(25.f);
  shape.setFillColor(sf::Color(120, 120, 120));
  shape.setPosition(sf::Vector2f(x, -50.f));

  speed = spd;
}

void Asteroid::update(float dt) { shape.move(sf::Vector2f(0.f, speed * dt)); }

void Asteroid::draw(sf::RenderWindow& window) { window.draw(shape); }

sf::FloatRect Asteroid::getBounds() const { return shape.getGlobalBounds(); }

float Asteroid::getY() const { return shape.getPosition().y; }
