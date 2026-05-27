#pragma once
#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "Card.h"

class Game {
 public:
  Game();
  void run();

 private:
  sf::RenderWindow window;
  sf::Font font;

  std::vector<Card> cards;

  int firstOpened = -1;
  int secondOpened = -1;

  int score = 0;
  int moves = 0;
  int wrongStreak = 0;

  bool waitingToClose = false;
  sf::Clock delayClock;

  bool showShuffleMessage = false;
  sf::Clock shuffleMessageClock;

  bool gameFinished = false;

 private:
  void initCards();
  void shuffleCards();
  void processEvents();
  void update();
  void render();

  void handleMouseClick(int mouseX, int mouseY);
  void checkPair();
  void closeWrongPair();
  void drawCard(const Card& card);
  bool allMatched() const;
};
