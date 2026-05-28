#include "Card.h"

Card::Card(int pairId, float x, float y, float size)
    : pairId(pairId), state(HIDDEN), size(size) {
  shape.setSize(sf::Vector2f(size, size));
  shape.setPosition(x, y);
  shape.setFillColor(sf::Color(100, 100, 200));  // цвет рубашки
  shape.setOutlineThickness(2);
  shape.setOutlineColor(sf::Color::Black);

  if (!font.loadFromFile("sunday.ttf")) {
    // запасной вариант Ц любой шрифт из системы, или можно оставить пустым
  }
  text.setFont(font);
  text.setString(std::string(1, 'A' + pairId));
  text.setCharacterSize(size * 0.6f);
  text.setFillColor(sf::Color::White);
  text.setStyle(sf::Text::Bold);
  // центрируем текст
  sf::FloatRect textRect = text.getLocalBounds();
  text.setOrigin(textRect.left + textRect.width / 2.0f,
                 textRect.top + textRect.height / 2.0f);
  text.setPosition(x + size / 2.0f, y + size / 2.0f);
}

void Card::draw(sf::RenderWindow& window) const {
  if (state != MATCHED) {
    window.draw(shape);
    if (state == REVEALED) {
      window.draw(text);
    }
  }
}

bool Card::contains(float mouseX, float mouseY) const {
  return shape.getGlobalBounds().contains(mouseX, mouseY);
}

void Card::reveal() {
  if (state == HIDDEN) {
    state = REVEALED;
    shape.setFillColor(
        sf::Color(220, 220, 220));  // светлый цвет лицевой стороны
  }
}

void Card::hide() {
  if (state == REVEALED) {
    state = HIDDEN;
    shape.setFillColor(sf::Color(100, 100, 200));  // обратно рубашка
  }
}

void Card::remove() { state = MATCHED; }

bool Card::isHidden() const { return state == HIDDEN; }
bool Card::isRevealed() const { return state == REVEALED; }
bool Card::isMatched() const { return state == MATCHED; }
int Card::getPairId() const { return pairId; }

void Card::setPosition(float x, float y) {
  shape.setPosition(x, y);
  text.setPosition(x + size / 2.0f, y + size / 2.0f);
}

sf::Vector2f Card::getPosition() const { return shape.getPosition(); }
