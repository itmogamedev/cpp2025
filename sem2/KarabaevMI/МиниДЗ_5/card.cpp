#include "card.h"

#include <string>

Card::Card()
    : symbol(' '),
      state(CardState::Hidden),
      position(0.f, 0.f),
      size(0.f, 0.f) {}

Card::Card(char symbol, sf::Vector2f position, sf::Vector2f size)
    : symbol(symbol),
      state(CardState::Hidden),
      position(position),
      size(size) {}

char Card::getSymbol() const { return symbol; }

void Card::setSymbol(char new_symbol) { symbol = new_symbol; }

CardState Card::getState() const { return state; }

void Card::setState(CardState new_state) { state = new_state; }

bool Card::contains(sf::Vector2f point) const {
  if (state == CardState::Matched) {
    return false;
  }
  return point.x >= position.x && point.x <= position.x + size.x &&
         point.y >= position.y && point.y <= position.y + size.y;
}

void Card::draw(sf::RenderWindow& window, const sf::Font& font,
                bool font_ready) const {
  if (state == CardState::Matched) {
    return;
  }

  sf::RectangleShape shape(size);
  shape.setPosition(position);
  shape.setOutlineThickness(3.f);
  shape.setOutlineColor(sf::Color(30, 30, 30));

  if (state == CardState::Hidden) {
    shape.setFillColor(sf::Color(70, 110, 170));
  } else {
    shape.setFillColor(sf::Color(240, 235, 215));
  }
  window.draw(shape);

  if (state == CardState::Revealed && font_ready) {
    sf::Text text;
    text.setFont(font);
    text.setString(std::string(1, symbol));
    text.setCharacterSize(static_cast<unsigned int>(size.y * 0.6f));
    text.setFillColor(sf::Color(30, 30, 30));
    text.setStyle(sf::Text::Bold);

    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.left + bounds.width / 2.f,
                   bounds.top + bounds.height / 2.f);
    text.setPosition(position.x + size.x / 2.f, position.y + size.y / 2.f);
    window.draw(text);
  }
}
