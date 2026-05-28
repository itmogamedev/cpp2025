#pragma once
#include <SFML/Graphics.hpp>

#include "card.h"

class Game {
  sf::RenderWindow window;
  std::vector<Card> cards;
  sf::Font font;
  int first_card, second_card, moves, fails, matched_pairs;
  bool delayFlag, gameOver, shuffleProcces;
  sf::Clock inputLock, shuffleTimer;

 public:
  Game();
  void runGame();
  void regInput();
  void update();
  void draw();
  void shuffle();
};
