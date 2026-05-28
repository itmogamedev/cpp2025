#include "Bullet.h"

Bullet::Bullet(const sf::Vector2f& position)
    : velocity(0.f, kSpeed), active(true) {
  shape.setSize(sf::Vector2f(kWidth, kHeight));
  shape.setFillColor(sf::Color::Yellow);
  shape.setPosition(position.x, position.y);
}

void Bullet::update(sf::Time delta_time) {
  float dt = delta_time.asSeconds();
  shape.move(velocity * dt);
}

void Bullet::draw(sf::RenderWindow& window) { window.draw(shape); }

bool Bullet::isActive() const { return active; }

sf::FloatRect Bullet::getBounds() const { return shape.getGlobalBounds(); }
