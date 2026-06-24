#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "card.h"

class game {
 private:
  sf::Font gameFont;
  sf::Text statusText;
  std::vector<card> gameCards;

  int firstCardIndex;
  int secondCardIndex;
  bool isWaitingDelay;
  sf::Clock delayClock;

  int consecutiveMistakes;
  int totalMoves;
  int pairsFound;
  bool isGameWon;

  void shuffleHiddenCards();
  int randNum(int minVal, int maxVal);

 public:
  game();
  void handleMouseClick(sf::Vector2i mousePosition);
  void updateLogic();
  void renderGame(sf::RenderWindow& appWindow);
};