#pragma once

#include <SFML/Graphics.hpp>

enum class CardState { Hidden, Revealed, Matched };

class Card {
 public:
  Card();
  Card(char symbol, sf::Vector2f position, sf::Vector2f size);

  void draw(sf::RenderWindow& window, const sf::Font& font,
            bool font_ready) const;
  bool contains(sf::Vector2f point) const;

  char getSymbol() const;
  void setSymbol(char new_symbol);

  CardState getState() const;
  void setState(CardState new_state);

 private:
  char symbol;
  CardState state;
  sf::Vector2f position;
  sf::Vector2f size;
};
