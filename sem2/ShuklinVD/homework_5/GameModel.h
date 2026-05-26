#pragma once
#include <vector>

#include "Asteroid.h"
#include "Bullet.h"
#include "Ship.h"

enum class GameState { Playing, GameOver };

class GameModel {
 public:
  GameModel(float screen_width, float screen_height);

  void reset();
  void update(float delta_time);

  void moveShipLeft(float delta_time);
  void moveShipRight(float delta_time);
  void shoot();

  const Ship& getShip() const;
  const std::vector<Asteroid>& getAsteroids() const;
  const std::vector<Bullet>& getBullets() const;
  int getScore() const;
  int getLives() const;
  GameState getState() const;

 private:
  void spawnAsteroid();
  void updateBullets(float delta_time);
  void updateAsteroids(float delta_time);
  void checkCollisions();
  void cleanupDeadObjects();
  float currentCooldown() const;

  float screen_width;
  float screen_height;

  Ship ship;
  std::vector<Asteroid> asteroids;
  std::vector<Bullet> bullets;

  int score;
  GameState state;

  float shoot_timer;
  float spawn_timer;
  float game_time;
  float spawn_interval;
};
