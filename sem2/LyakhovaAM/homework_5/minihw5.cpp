#include <iostream>

#include "Game.h"

void startGame() {
  sf::RenderWindow window(sf::VideoMode({800, 800}), "minihw5");
  window.setVerticalSyncEnabled(true);

  Game game = Game();

  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>())
        window.close();
      else {
        if (const auto* key_pressed = event->getIf<sf::Event::KeyPressed>())
          if (key_pressed->scancode == sf::Keyboard::Scancode::Escape)
            window.close();
        if (const auto* mouse = event->getIf<sf::Event::MouseButtonReleased>())
          game.turn(mouse->position);
      }
    }
    window.clear();
    window.draw(game);
    window.display();
    game.checkCards();
  }
}

int main() {
  startGame();
  return 0;
}
