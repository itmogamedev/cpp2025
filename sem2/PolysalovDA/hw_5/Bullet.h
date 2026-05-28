#pragma once
#include "Constants.h"
#include "Entity.h"

class Bullet : public Entity {
 public:
  Bullet(const sf::Texture& texture, const sf::Vector2f& position);

  void update(float delta_time) override;
  bool isOffScreen() const;

 private:
  float speed = BULLET_SPEED;
};