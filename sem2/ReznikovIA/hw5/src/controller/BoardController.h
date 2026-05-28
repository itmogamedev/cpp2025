#pragma once

#include <SFML/Graphics.hpp>

#include "../model/BoardModel.h"
#include "../view/BoardView.h"

class BoardController {
 public:
  BoardController(BoardModel& boardModel, BoardView& boardView);
  void handleEvent(const std::optional<sf::Event>& event);

 private:
  BoardModel& boardModel;
  BoardView& boardView;
};
