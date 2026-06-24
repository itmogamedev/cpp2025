#pragma once
#pragma once
#include <SFML/Graphics.hpp>
#include <string>

// используем сруктуру для более простых данных
struct Card {
  sf::RectangleShape shape;
  std::string symbol;

  bool isOpen = false;
  bool isMatched = false;
};
