#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <random>
#include <vector>

#include "Circle.h"

class Game {
 public:
  Game();
  void run();

 private:
  void processEvents();
  void update(float deltaTime);
  void render();
  void handleClick(const sf::Vector2f& mousePos);
  void resetCircle(Circle& circle);
  sf::Vector2f randomPosition();
  sf::Vector2f randomVelocity();

  sf::RenderWindow window;
  sf::Font font;
  sf::Text timerText;
  sf::Text scoreText;
  sf::Text gameOverText;
  sf::Text finalScoreText;

  std::vector<Circle> circles;
  std::mt19937 rng;
  std::uniform_real_distribution<float> distX;
  std::uniform_real_distribution<float> distY;
  std::uniform_real_distribution<float> distVel;

  sf::Clock clock;
  float timeLeft;
  int score;
  bool gameOver;
};

#endif
