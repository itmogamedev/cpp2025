#include "GameModel.h"

#include <cstdlib>

#include "constants.h"

GameModel::GameModel(float screen_width, float screen_height)
    : screen_width(screen_width), screen_height(screen_height) {
  reset();
}

void GameModel::reset() {
  asteroids.clear();
  bullets.clear();

  float ship_x = screen_width / 2.f - SHIP_SPAWN_OFFSET_X;
  float ship_y = screen_height - SHIP_SPAWN_OFFSET_Y;
  ship = Ship(ship_x, ship_y);

  score = 0;
  state = GameState::Playing;

  shoot_timer = 0.f;
  spawn_timer = 0.f;
  game_time = 0.f;
  spawn_interval = SPAWN_INTERVAL_INIT;
}

float GameModel::currentCooldown() const {
  float cooldown =
      SHOOT_COOLDOWN_BASE - static_cast<float>(score) * SHOOT_COOLDOWN_STEP;
  if (cooldown < SHOOT_COOLDOWN_MIN) cooldown = SHOOT_COOLDOWN_MIN;
  return cooldown;
}

void GameModel::update(float delta_time) {
  if (state != GameState::Playing) return;

  game_time += delta_time;
  shoot_timer += delta_time;
  spawn_timer += delta_time;

  if (spawn_timer >= spawn_interval) {
    spawnAsteroid();
    spawn_timer = 0.f;
  }

  updateBullets(delta_time);
  updateAsteroids(delta_time);
  checkCollisions();
  cleanupDeadObjects();

  if (ship.isDead()) state = GameState::GameOver;
}

void GameModel::spawnAsteroid() {
  float x = static_cast<float>(rand() %
                               static_cast<int>(screen_width - ASTEROID_WIDTH));
  float speed = ASTEROID_BASE_SPEED + game_time * ASTEROID_SPEED_ACCEL;
  Asteroid asteroid(x, ASTEROID_SPAWN_Y, speed);
  asteroids.push_back(asteroid);
}

void GameModel::moveShipLeft(float delta_time) {
  if (state == GameState::Playing) ship.moveLeft(delta_time, screen_width);
}

void GameModel::moveShipRight(float delta_time) {
  if (state == GameState::Playing) ship.moveRight(delta_time, screen_width);
}

void GameModel::shoot() {
  if (state != GameState::Playing) return;

  if (shoot_timer >= currentCooldown()) {
    float bullet_x = ship.getX() + ship.getWidth() / 2.f - BULLET_WIDTH / 2.f;
    float bullet_y = ship.getY() - BULLET_SPAWN_OFFSET_Y;
    bullets.push_back(Bullet(bullet_x, bullet_y));
    shoot_timer = 0.f;
  }
}

void GameModel::updateBullets(float delta_time) {
  for (size_t i = 0; i < bullets.size(); i++) {
    bullets[i].update(delta_time);
    if (bullets[i].getY() + bullets[i].getHeight() < 0.f) bullets[i].kill();
  }
}

void GameModel::updateAsteroids(float delta_time) {
  for (size_t i = 0; i < asteroids.size(); i++) {
    asteroids[i].update(delta_time);
    if (asteroids[i].getY() > screen_height) asteroids[i].kill();
  }
}

void GameModel::checkCollisions() {
  for (size_t b = 0; b < bullets.size(); b++) {
    if (!bullets[b].isAlive()) continue;

    for (size_t a = 0; a < asteroids.size(); a++) {
      if (!asteroids[a].isAlive()) continue;

      if (bullets[b].collidesWith(asteroids[a])) {
        bullets[b].kill();
        asteroids[a].kill();
        score += SCORE_PER_ASTEROID;
        break;
      }
    }
  }

  for (size_t a = 0; a < asteroids.size(); a++) {
    if (!asteroids[a].isAlive()) continue;

    if (ship.collidesWith(asteroids[a])) {
      asteroids[a].kill();
      ship.loseLife();
    }
  }
}

void GameModel::cleanupDeadObjects() {
  std::vector<Bullet> alive_bullets;
  for (size_t i = 0; i < bullets.size(); i++) {
    if (bullets[i].isAlive()) alive_bullets.push_back(bullets[i]);
  }
  bullets = alive_bullets;

  std::vector<Asteroid> alive_asteroids;
  for (size_t i = 0; i < asteroids.size(); i++) {
    if (asteroids[i].isAlive()) alive_asteroids.push_back(asteroids[i]);
  }
  asteroids = alive_asteroids;
}

const Ship& GameModel::getShip() const { return ship; }
const std::vector<Asteroid>& GameModel::getAsteroids() const {
  return asteroids;
}
const std::vector<Bullet>& GameModel::getBullets() const { return bullets; }
int GameModel::getScore() const { return score; }
int GameModel::getLives() const { return ship.getLives(); }
GameState GameModel::getState() const { return state; }
