#include "card.h"

Card::Card() : value_(0), is_revealed_(false), is_removed_(false) {}

void Card::initialize(float x, float y, int value, const sf::Font& font) {
  value_ = value;

  shape_.setSize(sf::Vector2f(100.0f, 100.0f));
  shape_.setPosition(x, y);
  shape_.setFillColor(sf::Color(70, 70, 200));
  shape_.setOutlineThickness(2.0f);
  shape_.setOutlineColor(sf::Color::Black);

  text_.setFont(font);
  text_.setString(std::to_string(value_));
  text_.setCharacterSize(42);
  text_.setFillColor(sf::Color::White);

  sf::FloatRect bounds = text_.getLocalBounds();

  text_.setOrigin(bounds.left + bounds.width / 2.0f,
                  bounds.top + bounds.height / 2.0f);

  text_.setPosition(x + 50.0f, y + 50.0f);
}

void Card::draw(sf::RenderWindow& window) const {
  if (is_removed_) {
    return;
  }

  window.draw(shape_);

  if (is_revealed_) {
    window.draw(text_);
  }
}

bool Card::contains(sf::Vector2f point) const {
  return shape_.getGlobalBounds().contains(point);
}

void Card::reveal() {
  is_revealed_ = true;
  shape_.setFillColor(sf::Color(120, 180, 255));
}

void Card::hide() {
  is_revealed_ = false;
  shape_.setFillColor(sf::Color(70, 70, 200));
}

void Card::remove() { is_removed_ = true; }

bool Card::isRevealed() const { return is_revealed_; }

bool Card::isRemoved() const { return is_removed_; }

int Card::getValue() const { return value_; }

void Card::setPosition(float x, float y) {
  shape_.setPosition(x, y);
  text_.setPosition(x + 50.0f, y + 50.0f);
}

sf::Vector2f Card::getPosition() const { return shape_.getPosition(); }
