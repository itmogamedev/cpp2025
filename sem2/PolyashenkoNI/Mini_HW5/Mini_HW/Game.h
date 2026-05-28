#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Card.h"

class Game {
 public:
  Game();
  void run();

 private:
  void processEvents();
  void update();
  void render();
  void shuffleHiddenCards();
  void checkMatch();
  void resetSelection();

  sf::RenderWindow window;
  std::vector<Card> cards;
  Card* firstSelected;
  Card* secondSelected;
  sf::Clock delayClock;
  bool waitingForDelay;
  int consecutiveErrors;
  int turns;
  int pairsFound;
  sf::Font font;
  sf::Text turnText;

  static const int GRID_SIZE = 4;
  static const float CARD_SIZE;
  static const float PADDING;
  static const float DELAY_SECONDS;
};
