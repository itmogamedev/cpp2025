#include "Bullet.h"

Bullet::Bullet(const sf::Texture& texture, const sf::Vector2f& position)
    : Entity(texture) {
  auto size = getSize();
  setScale(BULLET_SIZE.x / size.x, BULLET_SIZE.y / size.y);
  setPosition(position);
}

void Bullet::update(float delta_time) { move({0.f, -speed * delta_time}); }

bool Bullet::isOffScreen() const { return getPosition().y < BULLET_DESTROY_Y; }