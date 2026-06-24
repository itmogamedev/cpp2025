#include "engine.h"

engine::engine() : appWindow(sf::VideoMode(480, 550), "Memory Game") {
  appWindow.setFramerateLimit(60);
}

void engine::processEvents() {
  sf::Event eventWindow;
  while (appWindow.pollEvent(eventWindow)) {
    if (eventWindow.type == sf::Event::Closed) {
      appWindow.close();
    }
    if (eventWindow.type == sf::Event::MouseButtonPressed and
        eventWindow.mouseButton.button == sf::Mouse::Left) {
      sf::Vector2i mousePosition = sf::Mouse::getPosition(appWindow);
      gameObject.handleMouseClick(mousePosition);
    }
  }
}

void engine::updateGame() { gameObject.updateLogic(); }

void engine::renderGame() {
  appWindow.clear(sf::Color(40, 42, 54));
  gameObject.renderGame(appWindow);
  appWindow.display();
}

void engine::gameLoop() {
  while (appWindow.isOpen()) {
    processEvents();
    updateGame();
    renderGame();
  }
}