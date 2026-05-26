#pragma once
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

  sf::Clock bulletTimer;
  sf::Clock asteroidTimer;

  int score;
  int lives;
  float asteroidSpeed;
  float reloadTime;
  bool isGameOver;

  sf::Font font;
  sf::Text uiText;          
  sf::Text gameOverText;    
  sf::Text finalScoreText;  

  void initUI();
  void pollEvents();
  void updateEntities();
  void updateCollisions();
  void render();

 public:
  Game();
  void run();
};