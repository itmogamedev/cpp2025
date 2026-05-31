#include "Bullet.h"

Bullet::Bullet(float x, float y) {
  shape.setSize(sf::Vector2f(5.f, 20.f));
  shape.setFillColor(sf::Color::Green);
  shape.setPosition(sf::Vector2f(x, y));

  speed = 700.f;
}

void Bullet::update(float dt) { shape.move(sf::Vector2f(0.f, -speed * dt)); }

void Bullet::draw(sf::RenderWindow& window) { window.draw(shape); }

sf::FloatRect Bullet::getBounds() const { return shape.getGlobalBounds(); }

float Bullet::getY() const { return shape.getPosition().y; }
