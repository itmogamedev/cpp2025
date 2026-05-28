#include "Bullet.h"

#include "Constants.h"

Bullet::Bullet(float x, float y) : speed(kBulletSpeed) {
  shape.setSize(sf::Vector2f(kBulletWidth, kBulletHeight));
  shape.setFillColor(kBulletColor);
  shape.setPosition({x, y});
}

void Bullet::update(float dt) { shape.move({0.0f, -speed * dt}); }

void Bullet::draw(sf::RenderWindow& window) const { window.draw(shape); }

sf::FloatRect Bullet::getBounds() const { return shape.getGlobalBounds(); }

bool Bullet::isOffScreen(float windowHeight) const {
  return shape.getPosition().y + shape.getSize().y < 0.0f;
}
