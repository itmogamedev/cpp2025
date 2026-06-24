#pragma once
#include <SFML/Graphics.hpp>

enum class cardState { hidden, opened, solved };

class card {
 public:
  char cardSymbol;
  bool isOpened;
  bool isSolved;
  sf::RectangleShape cardShape;

  card(char symbol, float size, sf::Vector2f position);
  bool checkClick(sf::Vector2i mousePosition);
};
