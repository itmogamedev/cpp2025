#include "Card.h"

Card::Card()
    : symbol(0), state(CardState::kHidden), bounds(0.f, 0.f, 0.f, 0.f) {}

void Card::setSymbol(int symbol) { this->symbol = symbol; }

int Card::getSymbol() const { return symbol; }

void Card::setState(CardState state) { this->state = state; }

CardState Card::getState() const { return state; }

void Card::setBounds(float x, float y, float size) {
  bounds = sf::FloatRect(x, y, size, size);
}

bool Card::contains(float x, float y) const { return bounds.contains(x, y); }

void Card::draw(sf::RenderWindow& window, const sf::Texture& back_texture,
                const sf::Texture& face_texture) const {
  // Найденная пара исчезает с поля.
  if (state == CardState::kMatched) {
    return;
  }

  sf::RectangleShape shape(sf::Vector2f(bounds.width, bounds.height));
  shape.setPosition(bounds.left, bounds.top);
  shape.setOutlineThickness(3.f);
  shape.setOutlineColor(sf::Color(25, 30, 45));
  shape.setFillColor(sf::Color::White);

  if (state == CardState::kRevealed) {
    shape.setTexture(&face_texture);
  } else {
    shape.setTexture(&back_texture);
  }

  window.draw(shape);
}
