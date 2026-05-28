#include "BoardModel.h"
#include "../Constants.h"
#include <algorithm>
#include <random>
#include <chrono>

static std::mt19937& rng() {
    static std::mt19937 gen(static_cast<unsigned>(
        std::chrono::steady_clock::now().time_since_epoch().count()));
    return gen;
}

BoardModel::BoardModel() : moves(0), score(0), consecutiveMisses(0) {
    reset();
}

void BoardModel::reset() {
    cards.clear();
    flippedIndices.clear();
    moves = 0;
    score = 0;
    consecutiveMisses = 0;

    // Кладём по 2 экземпляра каждого id (0..7) и перемешиваем
    std::vector<int> symbols;
    for (int i = 0; i < PAIR_COUNT; ++i) {
        symbols.push_back(i);
        symbols.push_back(i);
    }
    std::shuffle(symbols.begin(), symbols.end(), rng());

    for (int i = 0; i < CARD_COUNT; ++i) {
        CardModel c;
        c.symbolId = symbols[i];
        c.row = i / GRID_SIZE;
        c.col = i % GRID_SIZE;
        cards.push_back(c);
    }
}

const std::vector<CardModel>& BoardModel::getCards() const { return cards; }

int BoardModel::getMoves() const { return moves; }
int BoardModel::getScore() const { return score; }

bool BoardModel::isFinished() const {
    return score >= PAIR_COUNT;
}

bool BoardModel::canFlip(int index) const {
    if (index < 0 || index >= (int)cards.size()) return false;
    if (flippedIndices.size() >= 2) return false;
    if (cards[index].state != CardState::Hidden) return false;
    return true;
}

void BoardModel::flip(int index) {
    if (!canFlip(index)) return;
    cards[index].state = CardState::Revealed;
    flippedIndices.push_back(index);
}

int BoardModel::flippedCount() const {
    return (int)flippedIndices.size();
}

void BoardModel::resolveFlipped() {
    if (flippedIndices.size() != 2) return;

    int a = flippedIndices[0];
    int b = flippedIndices[1];
    moves++;

    if (cards[a].symbolId == cards[b].symbolId) {
        cards[a].state = CardState::Matched;
        cards[b].state = CardState::Matched;
        score++;
        consecutiveMisses = 0;
    } else {
        cards[a].state = CardState::Hidden;
        cards[b].state = CardState::Hidden;
        consecutiveMisses++;

        // Две ошибки подряд — перемешиваем неоткрытые карточки
        if (consecutiveMisses >= 2) {
            shuffleHidden();
            consecutiveMisses = 0;
        }
    }

    flippedIndices.clear();
}

void BoardModel::shuffleHidden() {
    std::vector<int> hiddenIndices;
    std::vector<int> hiddenSymbols;

    for (int i = 0; i < (int)cards.size(); ++i) {
        if (cards[i].state == CardState::Hidden) {
            hiddenIndices.push_back(i);
            hiddenSymbols.push_back(cards[i].symbolId);
        }
    }

    std::shuffle(hiddenSymbols.begin(), hiddenSymbols.end(), rng());

    for (size_t i = 0; i < hiddenIndices.size(); ++i) {
        cards[hiddenIndices[i]].symbolId = hiddenSymbols[i];
    }
}
