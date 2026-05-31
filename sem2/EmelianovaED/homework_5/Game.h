#ifndef GAME_H
#define GAME_H
#include <vector>

#include "Cards.h"
class Game {
  std::vector<Card> board_game;
  int score_game;
  int score_moves;
  int score_errors;
  int first_id;
  int second_id;
  bool waiting_cards;

  void initBoard();
  void shuffleUnmatched();

 public:
  Game();
  void updateMatch();
  void handOpen(int id);
  bool isWaiting() const;
  bool isGameFinished() const;

  int getScore() const;
  int getMoves() const;
  const std::vector<Card>& getBoard() const;
};
#endif  // !GAME_H
