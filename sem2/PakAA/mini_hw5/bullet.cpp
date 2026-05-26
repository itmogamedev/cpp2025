#include "bullet.h"

Bullet::Bullet(float x, float y) : speed(620.f) {
  shape.setSize(sf::Vector2f(6.f, 18.f));
  shape.setOrigin(3.f, 9.f);
  shape.setPosition(x, y - 40.f);
  shape.setFillColor(sf::Color(255, 230, 80));
  shape.setOutlineThickness(1.f);
  shape.setOutlineColor(sf::Color(255, 140, 0));
}

void Bullet::update(float delta_time) {
  shape.move(0.f, -speed * delta_time);
}

void Bullet::draw(sf::RenderWindow& window) const { window.draw(shape); }

sf::FloatRect Bullet::getBounds() const { return shape.getGlobalBounds(); }

bool Bullet::isOffScreen() const { return shape.getPosition().y < -20.f; }
