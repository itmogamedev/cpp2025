//
// Created by Bakman Roman on 25.05.2026.
//

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>

class Game {
 public:
  Game();
  void run();

 private:
  void processEvents();
  void update(sf::Time deltaTime);
  void render();
  void resetGame();

  sf::RenderWindow window;
  sf::Font font;
  sf::Text uiText;
  sf::Text gameOverText;

  sf::ConvexShape player;
  float playerSpeed;
  int lives;
  int score;

  struct Bullet {
    sf::RectangleShape shape;
    float speed;
  };
  std::vector<Bullet> bullets;
  float baseReloadTime;
  float timeSinceLastFire;

  struct Asteroid {
    sf::CircleShape shape;
    float speed;
  };
  std::vector<Asteroid> asteroids;
  float asteroidSpawnTimer;
  float asteroidSpawnInterval;

  float gameTime;
  bool isGameOver;
};