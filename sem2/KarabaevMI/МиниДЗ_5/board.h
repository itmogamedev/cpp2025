#pragma once

#include <random>
#include <vector>

#include "card.h"

class Board {
 public:
  static constexpr int kRows = 4;
  static constexpr int kCols = 4;
  static constexpr int kCardCount = kRows * kCols;
  static constexpr int kPairCount = kCardCount / 2;

  Board(sf::Vector2f origin, sf::Vector2f card_size, float gap, unsigned seed);

  void draw(sf::RenderWindow& window, const sf::Font& font,
            bool font_ready) const;

  int findCardAt(sf::Vector2f point) const;

  Card& cardAt(int index);
  const Card& cardAt(int index) const;

  void shuffleHidden();
  bool allMatched() const;

 private:
  std::vector<Card> cards;
  std::mt19937 rng;

  void layoutCards(sf::Vector2f origin, sf::Vector2f card_size, float gap);
  void assignShuffledSymbols();
};
