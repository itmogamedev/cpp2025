#include "GameLogic.h"

#include "Constants.h"

GameLogic::GameLogic()
    : moves(0),
      firstCard(-1),
      secondCard(-1),
      waiting(false),
      gameWon(false),
      inChain(false),
      chainMultiplier(1),
      score(0) {}

void GameLogic::startDelay() {
  waiting = true;
  delayClock.restart();
}
bool GameLogic::isWaiting() const { return waiting; }
bool GameLogic::shouldResolve() const {
  return waiting && delayClock.getElapsedTime().asSeconds() > DELAY_SECONDS;
}
void GameLogic::resetSelection() {
  waiting = false;
  firstCard = -1;
  secondCard = -1;
}
void GameLogic::incrementMoves() { moves++; }
int GameLogic::getMoves() const { return moves; }
void GameLogic::setGameWon() { gameWon = true; }
bool GameLogic::isGameWon() const { return gameWon; }
int GameLogic::getFirstCard() const { return firstCard; }
int GameLogic::getSecondCard() const { return secondCard; }
void GameLogic::setFirstCard(int i) { firstCard = i; }
void GameLogic::setSecondCard(int i) { secondCard = i; }
void GameLogic::startChain() {
  chainMultiplier = inChain ? chainMultiplier + 1 : 1;
  inChain = true;
  chainClock.restart();
}
bool GameLogic::isChainActive() const {
  return inChain && chainClock.getElapsedTime().asSeconds() < CHAIN_BONUS_TIME;
}
int GameLogic::getChainMultiplier() const { return chainMultiplier; }
void GameLogic::resetChain() {
  inChain = false;
  chainMultiplier = 1;
}
void GameLogic::addScore(int p) { score += p * chainMultiplier; }
int GameLogic::getScore() const { return score; }
void GameLogic::updateChain() {
  if (inChain && chainClock.getElapsedTime().asSeconds() >= CHAIN_BONUS_TIME)
    resetChain();
}
