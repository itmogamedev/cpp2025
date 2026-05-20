#include "InputHandler.h"

#include <iostream>

InputHandler::InputHandler(sf::RenderWindow& win) : window(win) {}

InputState InputHandler::pollActions() {
  InputState state;

  while (auto event = window.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      window.close();
    }

    if (event->is<sf::Event::KeyPressed>()) {
      auto keyEvent = event->getIf<sf::Event::KeyPressed>();
      pressed_keys.insert(keyEvent->code);
    }

    if (event->is<sf::Event::KeyReleased>()) {
      auto keyEvent = event->getIf<sf::Event::KeyReleased>();
      pressed_keys.erase(keyEvent->code);
    }
  }

  bool left = pressed_keys.count(sf::Keyboard::Key::A) > 0 ||
              pressed_keys.count(sf::Keyboard::Key::Left) > 0;
  bool right = pressed_keys.count(sf::Keyboard::Key::D) > 0 ||
               pressed_keys.count(sf::Keyboard::Key::Right) > 0;
  bool space = pressed_keys.count(sf::Keyboard::Key::Space) > 0;

  if (left) {
    state.actions.push_back(Actions::MoveLeft);
  }
  if (right) {
    state.actions.push_back(Actions::MoveRight);
  }

  state.shooting = space;

  return state;
}