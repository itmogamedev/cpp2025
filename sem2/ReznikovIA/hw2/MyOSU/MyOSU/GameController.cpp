#include "GameController.h"

void GameController::run() {
  sf::Clock clock;
  model.reset();

  while (view.renderWindow.isOpen()) {
    float deltaTime = clock.restart().asSeconds();

    handleEvents();
    model.update(deltaTime);
    view.render();
  }
}

void GameController::handleEvents() {
  while (const std::optional event = view.renderWindow.pollEvent()) {
    if (event->is<sf::Event::Closed>())
      view.renderWindow.close();
    else if (const auto* mousePressed =
                 event->getIf<sf::Event::MouseButtonPressed>()) {
      if (mousePressed->button == sf::Mouse::Button::Left) {
        model.handleClick(mousePressed->position.x, mousePressed->position.y);
      }
    }
  }
}
