#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

#include "game.h"

sf::RenderWindow initWindow() {
  sf::VideoMode mode({800, 600});
  std::string title = "Typing Simulator 2026";

  sf::RenderWindow window(mode, title);

  window.setVerticalSyncEnabled(true);

  return window;
}

Game configureGame(int argc, char* argv[]) { return Game(); }

void processEvent(sf::RenderWindow& window, Game& game,
                  const sf::Event& event) {
  if (event.is<sf::Event::Closed>()) {
    window.close();
    return;
  }
  if (const auto* key_pressed = event.getIf<sf::Event::KeyPressed>()) {
    if (key_pressed->scancode == sf::Keyboard::Scancode::Enter) {
      game.startGame();
      return;
    }
  }
  if (const auto* text_entered = event.getIf<sf::Event::TextEntered>()) {
    game.processInput(text_entered->unicode);
    return;
  }
}

void gameLoop(sf::RenderWindow& window, Game& game) {
  while (window.isOpen()) {
    // Processing all events
    while (const std::optional event = window.pollEvent()) {
      processEvent(window, game, event);
    }

    // Drawing
    window.clear();
    window.draw(game);
    window.display();
  }
}

int main(int argc, char* argv[]) {
  srand(time(NULL));

  sf::RenderWindow window = initWindow();
  Game game = configureGame(argc, argv);

  gameLoop(window, game);

  return 0;
}
