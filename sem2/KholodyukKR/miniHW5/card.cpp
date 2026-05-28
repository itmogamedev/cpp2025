#include "card.h"

card::card(char symbol, float size, sf::Vector2f position) {
  cardSymbol = symbol;
  isOpened = false;
  isSolved = false;

  cardShape.setSize(sf::Vector2f(size, size));
  cardShape.setFillColor(sf::Color(70, 130, 180));
  cardShape.setPosition(position);
}

bool card::checkClick(sf::Vector2i mousePosition) {
  return cardShape.getGlobalBounds().contains(
      static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
}
