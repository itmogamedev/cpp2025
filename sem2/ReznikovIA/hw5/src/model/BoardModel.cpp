#include "BoardModel.h"

#include <algorithm>
#include <random>

static std::mt19937 rng(std::random_device{}());

BoardModel::BoardModel() {
  for (int i = 0; i < 8; i++) {
    cardModels.push_back(CardModel(i * 2, i));
    cardModels.push_back(CardModel(i * 2 + 1, i));
  }
  std::shuffle(cardModels.begin(), cardModels.end(), rng);
}

void BoardModel::shuffleFaceDown() {
  std::vector<int> faceDownIdx;
  for (int i = 0; i < (int)cardModels.size(); i++) {
    if (cardModels[i].cardState == CardState::FaceDown)
      faceDownIdx.push_back(i);
  }

  std::vector<CardModel> faceDownCards;
  for (int idx : faceDownIdx) faceDownCards.push_back(cardModels[idx]);

  std::shuffle(faceDownCards.begin(), faceDownCards.end(), rng);

  for (int i = 0; i < (int)faceDownIdx.size(); i++)
    cardModels[faceDownIdx[i]] = faceDownCards[i];
}

void BoardModel::update(float dt) {
  if (waitingToHide) {
    flipTimer -= dt;
    if (flipTimer <= 0.f) {
      cardModels[firstFlipped].cardState = CardState::FaceDown;
      cardModels[secondFlipped].cardState = CardState::FaceDown;
      firstFlipped = -1;
      secondFlipped = -1;
      waitingToHide = false;

      if (consecutiveErrors >= 2) {
        shuffleFaceDown();
        consecutiveErrors = 0;
      }
    }
  }

  if (waitingToMatch) {
    matchTimer -= dt;
    if (matchTimer <= 0.f) {
      cardModels[firstMatched].cardState = CardState::Matched;
      cardModels[secondMatched].cardState = CardState::Matched;
      firstMatched = -1;
      secondMatched = -1;
      waitingToMatch = false;
      score++;
      consecutiveErrors = 0;
    }
  }
}

void BoardModel::flipCard(int index) {
  if (waitingToHide || waitingToMatch) return;
  if (cardModels[index].cardState != CardState::FaceDown) return;

  cardModels[index].cardState = CardState::FaceUp;

  if (firstFlipped == -1) {
    firstFlipped = index;
  } else {
    secondFlipped = index;
    moves++;

    if (cardModels[firstFlipped].typeId == cardModels[secondFlipped].typeId) {
      firstMatched = firstFlipped;
      secondMatched = secondFlipped;
      firstFlipped = -1;
      secondFlipped = -1;
      waitingToMatch = true;
      matchTimer = matchDelay;
    } else {
      waitingToHide = true;
      flipTimer = flipDelay;
      consecutiveErrors++;
    }
  }
}
