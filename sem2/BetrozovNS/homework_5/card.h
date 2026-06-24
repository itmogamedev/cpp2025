#ifndef CARD_H_
#define CARD_H_

#include <SFML/Graphics.hpp>

class Card {
 public:
  Card();

  void initialize(float x, float y, int value, const sf::Font& font);

  void draw(sf::RenderWindow& window) const;

  bool contains(sf::Vector2f point) const;

  void reveal();
  void hide();
  void remove();

  bool isRevealed() const;
  bool isRemoved() const;

  int getValue() const;

  void setPosition(float x, float y);
  sf::Vector2f getPosition() const;

 private:
  sf::RectangleShape shape_;
  sf::Text text_;

  int value_;

  bool is_revealed_;
  bool is_removed_;
};

#endif  // CARD_H_
