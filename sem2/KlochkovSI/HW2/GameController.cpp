#include "GameController.h"

GameController::GameController(GameModel& model) : model_(model) {}

void GameController::handleEvent(const sf::Event& event) {
  if (model_.isGameOver()) return;

  if (const auto* mouse_event = event.getIf<sf::Event::MouseButtonPressed>()) {
    if (mouse_event->button == sf::Mouse::Button::Left) {
      sf::Vector2f mouse_pos(static_cast<float>(mouse_event->position.x),
                             static_cast<float>(mouse_event->position.y));
      handleMouseClick(mouse_pos);
    }
  }
}

void GameController::handleMouseClick(sf::Vector2f mouse_pos) {
  std::vector<Circle>& circles = model_.getCircles();
  for (int i = 0; i < static_cast<int>(circles.size()); ++i) {
    if (circles[i].isClicked(mouse_pos)) {
      model_.handleHit(i);
      return;
    }
  }
  model_.handleMiss();
}
