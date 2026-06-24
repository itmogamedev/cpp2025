#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Card {
 private:
  sf::RectangleShape shape;
  sf::Text text;
  sf::Font font;
  int pairId;
  enum State { HIDDEN, REVEALED, MATCHED } state;
  float size;

 public:
  Card(int pairId, float x, float y, float size);

  void draw(sf::RenderWindow& window) const;
  bool contains(float mouseX, float mouseY) const;
  void reveal();
  void hide();
  void remove();

  bool isHidden() const;
  bool isRevealed() const;
  bool isMatched() const;
  int getPairId() const;
  void setPosition(float x, float y);

  sf::Vector2f getPosition() const;
};
