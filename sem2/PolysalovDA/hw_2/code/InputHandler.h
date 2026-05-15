#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

enum class Actions { LeftClick };

class InputHandler {
 private:
  sf::RenderWindow& window;
  sf::Vector2i last_mouse_pos;

 public:
  InputHandler(sf::RenderWindow& win);
  std::vector<Actions> pollActions();
  sf::Vector2i getLastMousePosition() const;
};