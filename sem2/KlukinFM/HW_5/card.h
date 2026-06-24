#pragma once
#include <SFML/Graphics.hpp>

class Card {
  sf::RectangleShape shape;
  sf::Font font;
  char symbol;
  bool isOpen, isMatched;

 public:
  Card(float x, float y, float width, float height, char sym);
  sf::FloatRect getGlobalBounds() const { return shape.getGlobalBounds(); }
  bool getIsOpen() { return isOpen; }
  bool getIsMatched() { return isMatched; }
  char getSymbol() { return symbol; }

  void setIsOpen(bool state) { isOpen = state; }
  void setIsMatched(bool state) { isMatched = state; }
  void setSymbol(char ch) { symbol = ch; }

  void draw(sf::RenderWindow& window);
};
