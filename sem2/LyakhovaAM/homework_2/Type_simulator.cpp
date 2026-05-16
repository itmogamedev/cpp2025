#include <SFML/Graphics.hpp>
#include <iostream>

#include "Game.h"

void solve() {
  sf::RenderWindow window(sf::VideoMode({600, 600}), "Type_simulator");
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
        if (const auto* text_entered = event->getIf<sf::Event::TextEntered>())
          if (text_entered->unicode >= '0' && text_entered->unicode <= 'z')
            game.turn(text_entered->unicode);
      }
    }
    window.clear();
    window.draw(game);
    window.display();
  }
}

int main() {
  srand(time(NULL));
  solve();
  return 0;
}
