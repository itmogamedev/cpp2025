#ifndef GRAYJACK_BOARD_HPP_
#define GRAYJACK_BOARD_HPP_

#include "Card.hpp"

#include <array>

class Board {
 public:
  static constexpr int kCols = 4;
  static constexpr int kRows = 4;
  static constexpr int kTotal = kCols * kRows;

  explicit Board(const sf::Font& font);

  void Draw(sf::RenderWindow& window) const;
  int  CardAt(sf::Vector2f point) const;
  void FlipCard(int index);
  void HideFlipped();
  void MatchFlipped();
  void ShuffleUnmatched();
  bool AllMatched() const;

  const Card& GetCard(int i) const { return cards_[i]; }

 private:
  std::array<Card, kTotal> cards_;
  mutable sf::RectangleShape card_shape_;
  mutable sf::Text card_text_;

  static constexpr float kGap = 10.f;
  static constexpr float kOriginX = 25.f;
  static constexpr float kOriginY = 90.f;

  sf::Vector2f CardPos(int index) const;
  void DrawCard(sf::RenderWindow& window, const Card& card) const;
};

#endif  // GRAYJACK_BOARD_HPP_
