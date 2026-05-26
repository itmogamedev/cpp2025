#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <SFML/Graphics.hpp>

class GameLogic {
 private:
  int moves;
  int firstCard;
  int secondCard;
  bool waiting;
  bool gameWon;
  bool inChain;
  int chainMultiplier;
  int score;
  sf::Clock delayClock;
  sf::Clock chainClock;

 public:
  GameLogic();
  void startDelay();
  bool isWaiting() const;
  bool shouldResolve() const;
  void resetSelection();
  void incrementMoves();
  int getMoves() const;
  void setGameWon();
  bool isGameWon() const;
  int getFirstCard() const;
  int getSecondCard() const;
  void setFirstCard(int i);
  void setSecondCard(int i);
  void startChain();
  bool isChainActive() const;
  int getChainMultiplier() const;
  void resetChain();
  int getScore() const;
  void addScore(int p);
  void updateChain();
};

#endif
