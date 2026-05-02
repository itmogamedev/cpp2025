#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <memory>
#include <string>

class Game {
 public:
  Game();
  void run();

 private:
  void processEvents();
  void update(sf::Time dt);
  void render();
  void handleTextInput(char inputChar);
  void resetGame();
  void updateTexts();

  sf::RenderWindow window;
  sf::Font font;

  std::unique_ptr<sf::Text> scoreText;
  std::unique_ptr<sf::Text> timerText;
  std::unique_ptr<sf::Text> charText;
  std::unique_ptr<sf::Text> gameOverText;
  std::unique_ptr<sf::Text> restartText;

  bool gameActive;
  int score;
  float timeRemaining;
  char currentChar;

  sf::Clock clock;
};
