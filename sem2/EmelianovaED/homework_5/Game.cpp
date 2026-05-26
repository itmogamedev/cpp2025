#include "Game.h"

#include <algorithm>
#include <random>
#include <vector>
#define WIDTH_BOARD 4
#define HEIGHT_BOARD 4
#define TOTAL_CARDS (WIDTH_BOARD * HEIGHT_BOARD)
#define MAX_ERRORS 2
#define COEF 2
bool Game::isWaiting() const { return waiting_cards; }
int Game::getScore() const { return score_game; }
int Game::getMoves() const { return score_moves; }
const std::vector<Card>& Game::getBoard() const { return board_game; }
bool Game::isGameFinished() const {
  for (const auto& card : board_game) {
    if (!card.isMatched()) return false;
  }
  return true;
}
Game::Game()
    : score_game(0),
      score_moves(0),
      score_errors(0),
      first_id(-1),
      second_id(-1),
      waiting_cards(false) {
  initBoard();
}
void Game::initBoard() {
  board_game.resize(TOTAL_CARDS);
  for (int i = 0; i < TOTAL_CARDS; ++i) {
    board_game[i].setSymbol(i / COEF);
    board_game[i].setOpened(false);
    board_game[i].setMatched(false);
  }
  std::random_device rd;
  std::mt19937 rng(rd());
  std::shuffle(board_game.begin(), board_game.end(), rng);
}
void Game::shuffleUnmatched() {
  std::vector<int> symbols_cr;
  for (const auto& card : board_game) {
    if (!card.isMatched()) {
      symbols_cr.push_back(card.getSymbol());
    }
  }
  std::random_device rd;
  std::mt19937 rng(rd());
  std::shuffle(symbols_cr.begin(), symbols_cr.end(), rng);
  int idx_cr = 0;
  for (auto& card : board_game) {
    if (!card.isMatched()) {
      card.setSymbol(symbols_cr[idx_cr++]);
    }
  }
  score_errors = 0;
}
void Game::handOpen(int index) {
  if (waiting_cards) return;
  if (index < 0 || index >= TOTAL_CARDS) return;
  if (board_game[index].isMatched()) return;
  if (board_game[index].isOpened()) return;

  if (first_id == -1) {
    first_id = index;
    board_game[first_id].setOpened(true);
  } else if (second_id == -1 && index != first_id) {
    second_id = index;
    board_game[second_id].setOpened(true);
    waiting_cards = true;
  }
}
void Game::updateMatch() {
  if (!waiting_cards) return;
  if (first_id == -1 || second_id == -1) return;

  Card& card_one = board_game[first_id];
  Card& card_two = board_game[second_id];

  if (card_one.getSymbol() == card_two.getSymbol()) {
    card_one.setMatched(true);
    card_two.setMatched(true);
    score_game++;
    score_errors = 0;
  } else {
    score_errors++;
    if (score_errors >= MAX_ERRORS) {
      shuffleUnmatched();
    }
  }
  card_one.setOpened(false);
  card_two.setOpened(false);
  score_moves++;
  first_id = -1;
  second_id = -1;
  waiting_cards = false;
}
