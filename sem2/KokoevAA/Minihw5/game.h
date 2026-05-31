#ifndef GAME_H_
#define GAME_H_

#include <SFML/Graphics.hpp>
#include <cstddef>
#include <random>
#include <vector>

#include "asteroid.h"
#include "bullet.h"
#include "player.h"

class Game {
 public:
  Game();

  void run();

 private:
  void processEvents();
  void update(float delta_time);
  void render();
  void shoot();
  void spawnAsteroid(float delta_time);
  void updateObjects(float delta_time);
  void handleCollisions();
  void handlePlayerHit(std::size_t asteroid_index);
  void removeInactiveObjects();
  void drawHud();
  void drawGameOver();
  void restart();

  float getReloadDelay() const;
  float getAsteroidSpeed() const;
  float getRandomFloat(float min_value, float max_value);

  sf::RenderWindow window;
  sf::Font font;
  Player player;
  std::vector<Bullet> bullets;
  std::vector<Asteroid> asteroids;
  std::mt19937 random_engine;
  sf::Clock clock;
  sf::Clock shoot_clock;

  int score;
  int lives;
  float elapsed_time;
  float asteroid_spawn_timer;
  bool is_game_over;
  bool is_font_loaded;
};

#endif  // GAME_H_
