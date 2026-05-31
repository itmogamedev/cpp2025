#ifndef CARD_H
#define CARD_H

#include <SFML/Graphics.hpp>
#include <memory>

enum class CardState { Hidden, Opened, Matched };

class Card {
 private:
  char symbol_char;
  CardState current_state;
  sf::RectangleShape shape;
  std::unique_ptr<sf::Text> text;
  sf::Color back_color;
  sf::Color front_color;
  sf::Vector2f card_position;
  void updateTextAlignment();

 public:
  Card();
  void setSymbol(char symbol, const sf::Font& font);
  void setPosition(float x, float y);
  void setState(CardState state);
  CardState getState() const;
  char getSymbol() const;
  void draw(sf::RenderWindow& window);
  bool isClicked(sf::Vector2f mouse_pos) const;
};

#endif