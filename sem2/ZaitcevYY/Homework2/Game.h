#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "Circle.h"

class Game {
 public:
  Game();
  void run();

 private:
  void processEvents();
  void update();
  void render();
  void handleClick(sf::Vector2i mousePos);

  sf::RenderWindow window;
  std::vector<Circle> circles;

  int score;
  float timeLeft;
  bool isGameOver;

  sf::Font font;
  sf::Text scoreText;
  sf::Text timerText;
  sf::Text gameOverText;

  sf::Clock clock;
};
