#pragma once
#include <vector>

#include "CardModel.h"

class BoardModel {
 public:
  BoardModel();
  void update(float dt);
  void flipCard(int index);

  bool isGameOver() const { return score == 8; }

  int score = 0;
  int moves = 0;
  std::vector<CardModel> cardModels;

 private:
  void shuffleFaceDown();

  float flipTimer = 0.f;
  float flipDelay = 1.0f;
  bool waitingToHide = false;
  int firstFlipped = -1;
  int secondFlipped = -1;
  int consecutiveErrors = 0;

  bool waitingToMatch = false;
  float matchTimer = 0.f;
  float matchDelay = 1.0f;
  int firstMatched = -1;
  int secondMatched = -1;
};
