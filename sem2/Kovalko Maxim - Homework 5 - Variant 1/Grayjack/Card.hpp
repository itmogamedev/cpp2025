#ifndef GRAYJACK_CARD_HPP_
#define GRAYJACK_CARD_HPP_

#include <SFML/Graphics.hpp>

struct Card {
  enum class State { kFaceDown, kFaceUp, kMatched };
  static constexpr float kSize = 110.f;

  sf::String symbol;
  sf::Vector2f position;
  State state = State::kFaceDown;

  bool Contains(sf::Vector2f point) const;
};

#endif  // GRAYJACK_CARD_HPP_
