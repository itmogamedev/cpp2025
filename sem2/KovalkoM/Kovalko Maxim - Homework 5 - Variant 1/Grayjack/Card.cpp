#include "Card.hpp"

bool Card::Contains(sf::Vector2f point) const {
  if (state == State::kMatched) return false;
  return sf::FloatRect{position, {kSize, kSize}}.contains(point);
}
