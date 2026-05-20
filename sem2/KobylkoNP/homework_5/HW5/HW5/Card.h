#pragma once
#include <SFML/Graphics.hpp>
#include <string>

enum class CardState { Hidden, Revealed, Matched };

class Card {
 private:
  sf::RectangleShape shape;
  sf::Text symbolText;
  const sf::Font& font;
  std::string symbol;
  CardState state;
  sf::Vector2f position;

 public:
  Card(const sf::Font& font, const std::string& sym, float x, float y);
  void draw(sf::RenderWindow& window);
  bool contains(float mouseX, float mouseY) const;
  void reveal();
  void hide();
  void match();
  CardState getState() const;
  const std::string& getSymbol() const;
  void setPosition(float x, float y);
  sf::Vector2f getPosition() const;
};
