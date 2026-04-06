#pragma once
#include "typing.h"

#include <SFML/Graphics.hpp>

class Rendering {
 private:
  void SetupText(sf::Text& text, sf::Vector2f pos, unsigned int size);

  sf::Font font;
  sf::Text mainText;
  sf::Text scoreText;
  sf::Text timerText;

 public:
  Rendering();
  void Draw(sf::RenderWindow& window, const Typing& logic);
};