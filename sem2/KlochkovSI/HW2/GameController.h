#ifndef GAME_CONTROLLER_H_
#define GAME_CONTROLLER_H_

#include <SFML/Graphics.hpp>

#include "GameModel.h"

class GameController {
 public:
  explicit GameController(GameModel& model);

  void handleEvent(const sf::Event& event);

 private:
  void handleMouseClick(sf::Vector2f mouse_pos);

  GameModel& model_;
};

#endif  // GAME_CONTROLLER_H_
