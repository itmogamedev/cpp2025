#include "board.h"

#include <algorithm>
#include <cstddef>

Board::Board(sf::Vector2f origin, sf::Vector2f card_size, float gap,
             unsigned seed)
    : cards(kCardCount), rng(seed) {
  layoutCards(origin, card_size, gap);
  assignShuffledSymbols();
}

void Board::layoutCards(sf::Vector2f origin, sf::Vector2f card_size,
                        float gap) {
  for (int row = 0; row < kRows; ++row) {
    for (int col = 0; col < kCols; ++col) {
      sf::Vector2f pos(origin.x + static_cast<float>(col) * (card_size.x + gap),
                       origin.y + static_cast<float>(row) * (card_size.y + gap));
      cards[row * kCols + col] = Card(' ', pos, card_size);
    }
  }
}

void Board::assignShuffledSymbols() {
  std::vector<char> symbols;
  symbols.reserve(kCardCount);
  for (int i = 0; i < kPairCount; ++i) {
    char c = static_cast<char>('A' + i);
    symbols.push_back(c);
    symbols.push_back(c);
  }
  std::shuffle(symbols.begin(), symbols.end(), rng);
  for (int i = 0; i < kCardCount; ++i) {
    cards[i].setSymbol(symbols[i]);
  }
}

void Board::draw(sf::RenderWindow& window, const sf::Font& font,
                 bool font_ready) const {
  for (const auto& card : cards) {
    card.draw(window, font, font_ready);
  }
}

int Board::findCardAt(sf::Vector2f point) const {
  for (int i = 0; i < kCardCount; ++i) {
    if (cards[i].contains(point)) {
      return i;
    }
  }
  return -1;
}

Card& Board::cardAt(int index) { return cards[index]; }

const Card& Board::cardAt(int index) const { return cards[index]; }

void Board::shuffleHidden() {
  std::vector<int> indices;
  std::vector<char> symbols;
  for (int i = 0; i < kCardCount; ++i) {
    if (cards[i].getState() == CardState::Hidden) {
      indices.push_back(i);
      symbols.push_back(cards[i].getSymbol());
    }
  }
  std::shuffle(symbols.begin(), symbols.end(), rng);
  for (std::size_t i = 0; i < indices.size(); ++i) {
    cards[indices[i]].setSymbol(symbols[i]);
  }
}

bool Board::allMatched() const {
  return std::all_of(cards.begin(), cards.end(), [](const Card& c) {
    return c.getState() == CardState::Matched;
  });
}
