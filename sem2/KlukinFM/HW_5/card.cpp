#include "card.h"

Card::Card(float x, float y, float width, float height, char sym)
    : symbol(sym) {
  font.openFromFile("Comic Sans MS.ttf");
  shape.setSize(sf::Vector2f(width, height));
  shape.setPosition({x, y});
  isOpen = false;
  isMatched = false;
}

void Card::draw(sf::RenderWindow& window) {
  if (!isMatched) {
    sf::RectangleShape drawShape = shape;

    if (isOpen) {
      drawShape.setFillColor(sf::Color::Cyan);
      window.draw(drawShape);

      sf::Text text(font, symbol, 60);
      text.setFillColor(sf::Color::White);

      text.setPosition({shape.getPosition().x + shape.getSize().x / 2.0f - 20,
                        shape.getPosition().y + shape.getSize().y / 2.0f - 30});
      window.draw(text);
    } else {
      drawShape.setFillColor(sf::Color::Blue);
      window.draw(drawShape);
    }
  }
}
