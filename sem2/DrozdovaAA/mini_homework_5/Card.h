#pragma once
#include <SFML/Graphics.hpp>

struct Card {
  sf::RectangleShape shape;  // обьект в виде прямоугольника
  char symbol;               // буква на карточке
  bool is_face_up;           // открыта/закрыта
  bool is_matched;           // найдена ли пара

  Card(float x, float y, float width, float height, char sym);
  void draw(sf::RenderWindow& window, const sf::Font& font) const;
};
