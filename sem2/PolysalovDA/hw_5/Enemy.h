#pragma once
#include "Constants.h"
#include "Entity.h"

class Enemy : public Entity {
 private:
  float speed = ENEMY_SPEED;

 public:
  Enemy(const sf::Texture& texture);

  void update(float delta_time) override;
  void setSpeed(float new_speed);
};