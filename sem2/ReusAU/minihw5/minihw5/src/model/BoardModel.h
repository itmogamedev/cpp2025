#pragma once
#include <vector>
#include "CardModel.h"

class BoardModel {
public:
    BoardModel();

    void reset();

    const std::vector<CardModel>& getCards() const;

    int getMoves() const;
    int getScore() const;
    bool isFinished() const;

    bool canFlip(int index) const;
    void flip(int index);
    int flippedCount() const;

    // Проверить пару после задержки — совпала или нет
    void resolveFlipped();

    // Перемешать ещё не найденные карточки (после 2-х ошибок подряд)
    void shuffleHidden();

private:
    std::vector<CardModel> cards;
    std::vector<int> flippedIndices;
    int moves;
    int score;
    int consecutiveMisses;
};
