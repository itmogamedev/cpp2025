#include "Card.h"

#include "Constants.h"

Card::Card(const sf::Font& font, const std::string& sym, float x, float y)
    : font(font),
      symbol(sym),
      state(CardState::Hidden),
      position(x, y),
      symbolText(font) {
  shape.setSize(sf::Vector2f(CARD_WIDTH, CARD_HEIGHT));
  shape.setPosition(position);
  shape.setFillColor(CARD_HIDDEN_COLOR);
  shape.setOutlineThickness(CARD_OUTLINE_THICKNESS);
  shape.setOutlineColor(CARD_OUTLINE_COLOR);

  symbolText.setString("");
  symbolText.setCharacterSize(SYMBOL_CHARACTER_SIZE);
  symbolText.setFillColor(sf::Color::White);

  sf::FloatRect textRect = symbolText.getLocalBounds();
  symbolText.setOrigin(
      sf::Vector2f(textRect.position.x + textRect.size.x / 2.f,
                   textRect.position.y + textRect.size.y / 2.f));
  symbolText.setPosition(sf::Vector2f(position.x + CARD_WIDTH / 2.f,
                                      position.y + CARD_HEIGHT / 2.f));
}

void Card::draw(sf::RenderWindow& window) {
  if (state == CardState::Matched) return;

  if (state == CardState::Hidden) {
    shape.setFillColor(CARD_HIDDEN_COLOR);
    symbolText.setString("");
  } else {
    shape.setFillColor(CARD_REVEALED_COLOR);
    symbolText.setString(symbol);
  }

  window.draw(shape);
  window.draw(symbolText);
}

bool Card::contains(float mouseX, float mouseY) const {
  return shape.getGlobalBounds().contains(sf::Vector2f(mouseX, mouseY));
}

void Card::reveal() { state = CardState::Revealed; }

void Card::hide() { state = CardState::Hidden; }

void Card::match() { state = CardState::Matched; }

CardState Card::getState() const { return state; }

const std::string& Card::getSymbol() const { return symbol; }

void Card::setPosition(float x, float y) {
  position = sf::Vector2f(x, y);
  shape.setPosition(position);

  sf::FloatRect textRect = symbolText.getLocalBounds();
  symbolText.setOrigin(
      sf::Vector2f(textRect.position.x + textRect.size.x / 2.f,
                   textRect.position.y + textRect.size.y / 2.f));
  symbolText.setPosition(sf::Vector2f(position.x + CARD_WIDTH / 2.f,
                                      position.y + CARD_HEIGHT / 2.f));
}

sf::Vector2f Card::getPosition() const { return position; }
