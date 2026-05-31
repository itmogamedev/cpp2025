#include "BulletSystem.h"

void BulletSystem::addBullet(const Bullet& bullet) {
  bullets.push_back(bullet);
}

void BulletSystem::update(float delta_time) {
  for (auto it = bullets.begin(); it != bullets.end();) {
    it->update(delta_time);
    if (it->isOffScreen()) {
      it = bullets.erase(it);
    } else {
      ++it;
    }
  }
}

void BulletSystem::clear() { bullets.clear(); }

std::vector<Bullet>& BulletSystem::getBullets() { return bullets; }

const std::vector<Bullet>& BulletSystem::getBullets() const { return bullets; }