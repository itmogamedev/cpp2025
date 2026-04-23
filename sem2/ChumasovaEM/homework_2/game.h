#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

#include "input.h"
#include "score.h"
#include "symbol.h"
#include "timer.h"

class Game {
 public:
  Game();
  void run();

 private:
  void processEvents();
  void update(float deltaTime);
  void render();
  void initTexts();
  void newSymbol();

  sf::RenderWindow window;
  sf::Clock deltaClock;
  sf::Font font;

  bool playing;
  float timeLeft;
  int score;
  char currentSymbol;

  std::unique_ptr<sf::Text> symbolText;
  std::unique_ptr<sf::Text> scoreText;
  std::unique_ptr<sf::Text> timerText;
  std::unique_ptr<sf::Text> gameOverText;

  SymbolGenerator symbolGenerator;
  InputHandler inputHandler;
  Timer timer;
  Score scoreManager;
};
