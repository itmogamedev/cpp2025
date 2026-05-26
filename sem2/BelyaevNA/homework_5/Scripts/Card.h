#ifndef CARD_H
#define CARD_H

#include <SFML/Graphics.hpp>

enum class CardState { Hidden, Revealed, Matched };

class Card {
 private:
  sf::RectangleShape background;
  sf::Sprite coverSprite;
  sf::Sprite iconSprite;
  int symbolIndex;
  CardState state;
  bool wasSeen;

 public:
  Card(const sf::Texture& coverTex, const sf::Texture& iconTex);
  Card(const sf::Vector2f& position, int symbol, const sf::Texture& coverTex,
       const sf::Texture& iconTex);
  bool contains(const sf::Vector2i& point) const;
  void reveal();
  void hide();
  void match();
  void setSymbol(int newSymbol, const sf::Texture& iconTex);
  CardState getState() const;
  int getSymbolIndex() const;
  bool getWasSeen() const;
  void draw(sf::RenderWindow& window) const;
};

#endif
