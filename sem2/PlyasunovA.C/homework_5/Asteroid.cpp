#include "Asteroid.h"

#include <cstdlib>

Asteroid::Asteroid(const sf::Vector2f& position, float base_speed) {
  float radius = 20.f;
  shape.setRadius(radius);
  shape.setFillColor(sf::Color(128, 128, 128));
  shape.setOutlineColor(sf::Color::White);
  shape.setOutlineThickness(1.f);
  shape.setPosition(position);
  float speed = base_speed + (std::rand() % 50 - 25);
  velocity = sf::Vector2f(0.f, speed);
}

void Asteroid::update(sf::Time delta_time) {
  float dt = delta_time.asSeconds();
  shape.move(velocity * dt);
}

void Asteroid::draw(sf::RenderWindow& window) { window.draw(shape); }

sf::FloatRect Asteroid::getBounds() const { return shape.getGlobalBounds(); }

bool Asteroid::isOutOfBounds(float window_height) const {
  return shape.getPosition().y > window_height + shape.getRadius() * 2;
}

void Asteroid::setSize(float radius) { shape.setRadius(radius); }
