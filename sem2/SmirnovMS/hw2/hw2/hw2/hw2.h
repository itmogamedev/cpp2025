#pragma once

#include <SFML/Graphics.hpp>
#include <random>

class Game {
 public:
  Game();
  void run();

 private:
  void processEvents();
  void update(float dt);
  void render();

  void reset();
  void newChar();
  void handleInput(char c);

 private:
  sf::RenderWindow window;
  sf::Font font;

  sf::Text targetText;
  sf::Text scoreText;
  sf::Text timeText;
  sf::Text endText;

  std::mt19937 rng;
  std::uniform_int_distribution<int> dist;

  char currentChar;
  int score;
  float timeLeft;
  float penalty;
  bool isGameOver;

  sf::Clock clock;
};