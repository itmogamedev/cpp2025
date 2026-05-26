#pragma once
#include <SFML/Graphics.hpp>
#include <set>
#include <vector>

enum class Actions { MoveLeft, MoveRight };

struct InputState {
  std::vector<Actions> actions;
  bool shooting = false;
};

class InputHandler {
 public:
  InputHandler(sf::RenderWindow& win);
  InputState pollActions();

 private:
  sf::RenderWindow& window;
  std::set<sf::Keyboard::Key> pressed_keys;
};