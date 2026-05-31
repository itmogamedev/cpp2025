#include "Enemy.h"

#include "Constants.h"

Enemy::Enemy(const sf::Texture& texture) : Entity(texture) {
  auto size = getSize();
  setOrigin({size.x * SPRITE_SIZE_MULTIPLIER, size.y * SPRITE_SIZE_MULTIPLIER});
}

void Enemy::update(float delta_time) { move({0.f, speed * delta_time}); }

void Enemy::setSpeed(float new_speed) { speed = new_speed; }