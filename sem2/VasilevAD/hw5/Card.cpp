#include "Card.h"

Card::Card() {
  current_state = CardState::Hidden;
  shape.setSize({90.0f, 90.0f});
  back_color = sf::Color(134, 190, 126);
  front_color = sf::Color(206, 255, 199);
  shape.setFillColor(back_color);
  shape.setOutlineThickness(2.0f);
  shape.setOutlineColor(sf::Color::Black);
  symbol_char = ' ';
  card_position = {0.0f, 0.0f};
}

void Card::setSymbol(char symbol, const sf::Font& font) {
  symbol_char = symbol;
  text = std::make_unique<sf::Text>(font, std::string(1, symbol), 40);
  text->setFillColor(sf::Color(134, 190, 126));
  updateTextAlignment();
}

void Card::setPosition(float x, float y) {
  card_position = {x, y};
  shape.setPosition(card_position);
  updateTextAlignment();
}

void Card::updateTextAlignment() {
  if (text) {
    sf::FloatRect bounds = text->getLocalBounds();
    text->setOrigin({bounds.position.x + bounds.size.x / 2.0f,
                     bounds.position.y + bounds.size.y / 2.0f});
    text->setPosition({card_position.x + 45.0f, card_position.y + 45.0f});
  }
}

void Card::setState(CardState state) {
  current_state = state;
  shape.setFillColor((state == CardState::Hidden) ? back_color : front_color);
}

CardState Card::getState() const { return current_state; }
char Card::getSymbol() const { return symbol_char; }

void Card::draw(sf::RenderWindow& window) {
  if (current_state == CardState::Matched) return;
  window.draw(shape);
  if (current_state == CardState::Opened && text) {
    window.draw(*text);
  }
}

bool Card::isClicked(sf::Vector2f mouse_pos) const {
  return shape.getGlobalBounds().contains(mouse_pos);
}