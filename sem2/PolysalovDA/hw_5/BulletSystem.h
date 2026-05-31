#pragma once
#include <vector>

#include "Bullet.h"

class BulletSystem {
 public:
  void addBullet(const Bullet& bullet);
  void update(float delta_time);
  void clear();

  std::vector<Bullet>& getBullets();
  const std::vector<Bullet>& getBullets() const;

 private:
  std::vector<Bullet> bullets;
};