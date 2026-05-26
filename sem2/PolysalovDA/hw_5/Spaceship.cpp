#include "Spaceship.h"

Spaceship::Spaceship(const sf::Texture& texture, const sf::Texture& bullet_tex)
    : Entity(texture), bullet_texture(bullet_tex) {
  shoot_clock.restart();
}

void Spaceship::moveLeft(float delta_time) {
  sf::Vector2f pos = getPosition();
  if (pos.x > 0) {
    move({-speed * delta_time, 0.f});
  }
}

void Spaceship::moveRight(float delta_time) {
  sf::Vector2f pos = getPosition();
  if (pos.x + getSize().x < WINDOW_SIZE.x) {
    move({speed * delta_time, 0.f});
  }
}

std::optional<Bullet> Spaceship::tryShoot() {
  float current_time = shoot_clock.getElapsedTime().asSeconds();

  if (current_time - last_shot_time >= shoot_cooldown) {
    sf::Vector2f shoot_pos = getShootPosition();
    last_shot_time = current_time;
    return Bullet(bullet_texture, shoot_pos);
  }

  return std::nullopt;
}

void Spaceship::reduceCooldown(float amount) {
  shoot_cooldown = std::max(SHOOT_COOLDOWN_BASE - amount, SHOOT_COOLDOWN_MIN);
}

sf::Vector2f Spaceship::getShootPosition() const {
  sf::Vector2f ship_position = getPosition();
  float shoot_position_x = ship_position.x +
                           getSize().x * SPRITE_SIZE_MULTIPLIER -
                           BULLET_SIZE.x * SPRITE_SIZE_MULTIPLIER;
  float shoot_position_y = ship_position.y - BULLET_SIZE.y;
  return {shoot_position_x, shoot_position_y};
}