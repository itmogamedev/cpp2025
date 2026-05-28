#include "EnemySystem.h"

#include <cstdlib>
#include <iostream>

#include "Constants.h"
#include "Renderer.h"

EnemySystem::EnemySystem() {
  if (!enemy_texture.loadFromFile(ENEMY_TEXTURE)) {
    std::cerr << "Failed to load enemy texture" << std::endl;
  }
}

void EnemySystem::update(float delta_time, float speed) {
  current_speed = speed;
  for (auto it = enemies.begin(); it != enemies.end();) {
    it->setSpeed(speed);
    it->update(delta_time);

    if (it->getPosition().y > WINDOW_SIZE.y + WINDOW_PADDING) {
      it = enemies.erase(it);
    } else {
      ++it;
    }
  }
}

void EnemySystem::spawnEnemy(const sf::Vector2f& position) {
  Enemy enemy(enemy_texture);
  auto enemy_size = enemy.getSize();
  enemy.setScale(ENEMY_WIDTH / enemy_size.x, ENEMY_HEIGHT / enemy_size.y);
  enemy.setPosition(position);
  enemy.setSpeed(current_speed);
  enemies.push_back(std::move(enemy));
}

void EnemySystem::draw(Renderer& renderer) {
  for (const auto& enemy : enemies) {
    renderer.draw(enemy);
  }
}

void EnemySystem::clear() { enemies.clear(); }

std::vector<Enemy>& EnemySystem::getEnemies() { return enemies; }