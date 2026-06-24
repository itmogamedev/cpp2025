#include "Card.h"

Card::Card() : text(font) {
  if (!font.openFromFile("font/Cyrulik.otf")) exit(1);
  shape.setSize(sf::Vector2f(100.f, 100.f));
  shape.setFillColor(sf::Color(160, 60, 230));
  shape.setOutlineThickness(2.f);
  shape.setOutlineColor(sf::Color::White);
}

void Card::draw(sf::RenderWindow& window) {
  if (matched) return;

  if (revealed)
    shape.setFillColor(sf::Color::White);
  else
    shape.setFillColor(sf::Color(160, 60, 230));

  window.draw(shape);

  if (revealed) window.draw(text);
}

bool Card::contains(sf::Vector2f point) {
  return shape.getGlobalBounds().contains(point);
}
