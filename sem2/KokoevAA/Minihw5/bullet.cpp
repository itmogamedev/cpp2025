#include "bullet.h"

#include "constants.h"

Bullet::Bullet(sf::Vector2f position) {
  shape.setRadius(constants::kBulletRadius);
  shape.setOrigin({constants::kBulletRadius, constants::kBulletRadius});
  shape.setPosition(position);
  shape.setFillColor(sf::Color(255, 230, 120));
}

void Bullet::update(float delta_time) {
  shape.move({0.0F, -constants::kBulletSpeed * delta_time});
}

void Bullet::draw(sf::RenderWindow& window) const { window.draw(shape); }

bool Bullet::isOutOfWindow() const {
  return shape.getPosition().y + constants::kBulletRadius < 0.0F;
}

sf::FloatRect Bullet::getBounds() const { return shape.getGlobalBounds(); }
