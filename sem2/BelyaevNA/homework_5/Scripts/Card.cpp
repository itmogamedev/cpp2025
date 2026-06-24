#include "Card.h"

#include <algorithm>

#include "Constants.h"

Card::Card(const sf::Texture& coverTex, const sf::Texture& iconTex)
    : coverSprite(coverTex),
      iconSprite(iconTex),
      symbolIndex(0),
      state(CardState::Hidden),
      wasSeen(false) {
  background.setSize(sf::Vector2f(CARD_SIZE, CARD_SIZE));
  background.setFillColor(sf::Color(COLOR_BG_R, COLOR_BG_G, COLOR_BG_B));
  background.setOutlineThickness(CARD_OUTLINE);
  background.setOutlineColor(
      sf::Color(COLOR_GOLD_R, COLOR_GOLD_G, COLOR_GOLD_B));
}

Card::Card(const sf::Vector2f& position, int symbol,
           const sf::Texture& coverTex, const sf::Texture& iconTex)
    : coverSprite(coverTex),
      iconSprite(iconTex),
      symbolIndex(symbol),
      state(CardState::Hidden),
      wasSeen(false) {
  background.setSize(sf::Vector2f(CARD_SIZE, CARD_SIZE));
  background.setPosition(position);
  background.setFillColor(sf::Color(COLOR_BG_R, COLOR_BG_G, COLOR_BG_B));
  background.setOutlineThickness(CARD_OUTLINE);
  background.setOutlineColor(
      sf::Color(COLOR_GOLD_R, COLOR_GOLD_G, COLOR_GOLD_B));

  float innerSize = CARD_SIZE - 2 * CARD_PADDING;
  float coverScaleX = innerSize / coverTex.getSize().x;
  float coverScaleY = innerSize / coverTex.getSize().y;
  float coverScale = std::min(coverScaleX, coverScaleY);
  float coverOffsetX = (innerSize - coverTex.getSize().x * coverScale) / 2.0f;
  float coverOffsetY = (innerSize - coverTex.getSize().y * coverScale) / 2.0f;
  coverSprite.setScale({coverScale, coverScale});
  coverSprite.setPosition({position.x + CARD_PADDING + coverOffsetX,
                           position.y + CARD_PADDING + coverOffsetY});

  float iconScaleX = innerSize / iconTex.getSize().x;
  float iconScaleY = innerSize / iconTex.getSize().y;
  float iconScale = std::min(iconScaleX, iconScaleY);
  float iconOffsetX = (innerSize - iconTex.getSize().x * iconScale) / 2.0f;
  float iconOffsetY = (innerSize - iconTex.getSize().y * iconScale) / 2.0f;
  iconSprite.setScale({iconScale, iconScale});
  iconSprite.setPosition({position.x + CARD_PADDING + iconOffsetX,
                          position.y + CARD_PADDING + iconOffsetY});
}

bool Card::contains(const sf::Vector2i& point) const {
  return background.getGlobalBounds().contains(sf::Vector2f(point));
}

void Card::reveal() {
  state = CardState::Revealed;
  wasSeen = true;
}
void Card::hide() { state = CardState::Hidden; }

void Card::match() {
  state = CardState::Matched;
  background.setFillColor(
      sf::Color(COLOR_MATCH_R, COLOR_MATCH_G, COLOR_MATCH_B));
  background.setOutlineColor(sf::Color(0, 255, 0));
}

void Card::setSymbol(int newSymbol, const sf::Texture& iconTex) {
  symbolIndex = newSymbol;
  iconSprite.setTexture(iconTex);
}

CardState Card::getState() const { return state; }
int Card::getSymbolIndex() const { return symbolIndex; }
bool Card::getWasSeen() const { return wasSeen; }

void Card::draw(sf::RenderWindow& window) const {
  window.draw(background);
  if (state == CardState::Hidden)
    window.draw(coverSprite);
  else
    window.draw(iconSprite);
}
