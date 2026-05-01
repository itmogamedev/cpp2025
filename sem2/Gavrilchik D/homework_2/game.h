#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "Circle.h"

class Game {
 public:
  Game();
  void run();

 private:
  void processEvents();
  void update(float dt);
  void render();
  void handleClick(sf::Vector2f pos);

  sf::RenderWindow window_;
  std::vector<Circle> circles_;

  int score_;
  float timeLeft_;
  bool gameOver_;

  sf::Font font_;
  sf::Text scoreText_;
  sf::Text timeText_;
};

#endif