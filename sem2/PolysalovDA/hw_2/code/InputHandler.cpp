#include "InputHandler.h"

InputHandler::InputHandler(sf::RenderWindow& win) : window(win) {}

std::vector<Actions> InputHandler::pollActions() {
  std::vector<Actions> actions;

  while (auto event = window.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      window.close();
    }

    if (const auto* mouse_pressed =
            event->getIf<sf::Event::MouseButtonPressed>()) {
      if (mouse_pressed->button == sf::Mouse::Button::Left) {
        last_mouse_pos = mouse_pressed->position;
        actions.push_back(Actions::LeftClick);
      }
    }
  }
  return actions;
}

sf::Vector2i InputHandler::getLastMousePosition() const {
  return last_mouse_pos;
}