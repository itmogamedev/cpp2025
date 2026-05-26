#include "Bullet.h"

Bullet::Bullet(float posX, float posY) {
  shape.setSize(sf::Vector2f(5.f, 15.f));
  shape.setFillColor(sf::Color::Yellow);
  shape.setPosition(sf::Vector2f(posX, posY));
  movementSpeed = 10.f;
}

void Bullet::update() { shape.move(sf::Vector2f(0.f, -movementSpeed)); }

void Bullet::render(sf::RenderTarget& target) const { target.draw(shape); }

sf::FloatRect Bullet::getBounds() const { return shape.getGlobalBounds(); }

float Bullet::getPositionY() const { return shape.getPosition().y; }