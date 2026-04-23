#pragma once
#include "Constants.h"
#include "Object.h"
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

class Game {
public:
  int score;
  float timing;
  bool gameOver;
  std::vector<Object> objects;

  sf::Font font;
  sf::Text textForScore;
  sf::Text textForTimer;
  sf::Text textForGameOver;

  Game();
  sf::Vector2f randPosition();
  void start();
};