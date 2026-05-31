#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "Enemy.h"

class EnemySystem {
 private:
  std::vector<Enemy> enemies;
  sf::Texture enemy_texture;
  float current_speed = ENEMY_SPEED;

 public:
  EnemySystem();

  void update(float delta_time, float speed);
  void spawnEnemy(const sf::Vector2f& position);
  void draw(class Renderer& renderer);
  void clear();
  std::vector<Enemy>& getEnemies();
};