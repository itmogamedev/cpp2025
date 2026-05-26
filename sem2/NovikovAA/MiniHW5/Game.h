#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <optional>
#include <vector>

#include "Asteroid.h"
#include "Bullet.h"
#include "Player.h"

class Game {
 private:
  sf::RenderWindow window;

  Player player;

  std::vector<Bullet> bullets;
  std::vector<Asteroid> asteroids;

  sf::Clock deltaClock;
  sf::Clock shootClock;
  sf::Clock asteroidClock;

  sf::Font font;

  std::optional<sf::Text> scoreText;
  std::optional<sf::Text> livesText;
  std::optional<sf::Text> gameOverText;

  int score;
  int lives;

  bool gameOver;

  float asteroidSpeed;

 public:
  Game();

  void run();

 private:
  void processEvents();

  void update(float dt);

  void render();

  void shoot();

  void spawnAsteroid();

  float getShootCooldown();
};

#endif
