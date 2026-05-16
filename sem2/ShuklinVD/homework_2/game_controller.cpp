#include "game_controller.h"

#include <optional>

void GameController::handleEvents() {
  while (const std::optional event = view.getWindow().pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      view.getWindow().close();
    }

    if (const auto* mousePressed =
            event->getIf<sf::Event::MouseButtonPressed>()) {
      if (mousePressed->button == sf::Mouse::Button::Left) {
        sf::Vector2f click_position(
            static_cast<float>(mousePressed->position.x),
            static_cast<float>(mousePressed->position.y));

        bool is_good_click = false;
        for (int i = 0; i < model.getCircles().size(); i++) {
          if (model.getCircles()[i].getBounds().contains(click_position)) {
            model.getCircles().erase(model.getCircles().begin() + i);
            model.addPoints(5);
            is_good_click = true;
            view.updateScoreText(model);
            model.spawnCircle(model.getCircles());
            break;
          }
        }
        if (!is_good_click) {
          model.penaltyTime(PENALTY_SIZE);
        }
      }
    }
  }
}

void GameController::run() {
  model.initiateGame();
  while (view.isOpen()) {
    handleEvents();
    model.update();
    view.render(model);
  }
}
