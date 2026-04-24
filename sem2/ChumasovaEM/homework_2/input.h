#pragma once
#include <SFML/Window.hpp>

class InputHandler {
 public:
  char getPressedChar(sf::Keyboard::Key key) const;
};
