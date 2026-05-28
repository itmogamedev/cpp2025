#ifndef GAME_H
#define GAME_H

#include <vector>

#include "card.h"

class Game {
  std::vector<Card> playing_field;
  int player_score;
  int total_attempts;
  int error_counter;
  int first_card_index;
  int second_card_index;
  bool is_waiting_state;

  void initializeField();
  void shuffleRemaining();

 public:
  Game();
  void processMatch();
  void openCard(int id);
  bool isWaiting() const;
  bool isGameComplete() const;
  int getScore() const;
  int getMoves() const;
  const std::vector<Card>& getField() const;
};

#endif