#pragma once
#include <optional>

#include "Bullet.h"
#include "Constants.h"
#include "Entity.h"

class Spaceship : public Entity {
 public:
  Spaceship(const sf::Texture& texture, const sf::Texture& bullet_texture);

  void moveLeft(float delta_time);
  void moveRight(float delta_time);

  std::optional<Bullet> tryShoot();
  void reduceCooldown(float amount);

 private:
  const sf::Texture& bullet_texture;
  float speed = SHIP_SPEED;
  sf::Clock shoot_clock;
  float last_shot_time = 0.f;
  float shoot_cooldown = SHOOT_COOLDOWN_BASE;

  sf::Vector2f getShootPosition() const;
};