#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <vector>

#include "Asteroid.h"
#include "Bullet.h"
#include "Player.h"

class Game {
 public:
  Game();
  void run();

 private:
  void processEvents();
  void update(float dt);
  void render();
  void spawnAsteroid();
  void checkCollisions();
  float computeCooldown(int score) const;

  sf::RenderWindow window;
  sf::Font font;
  sf::Text scoreText;
  sf::Text livesText;
  sf::Text gameOverText;
  sf::Text finalScoreText;

  Player player;
  std::vector<Bullet> bullets;
  std::vector<Asteroid> asteroids;

  int score;
  float asteroidSpawnTimer;
  float asteroidSpawnInterval;
  float timeElapsed;
  bool gameOver;
};

#endif
