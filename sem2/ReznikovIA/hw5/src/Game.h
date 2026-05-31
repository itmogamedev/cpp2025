#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "controller/BoardController.h"
#include "model/BoardModel.h"
#include "view/BoardView.h"

class Game {
 public:
  Game();
  void run();

 private:
  sf::RenderWindow window;
  BoardModel boardModel;
  BoardView boardView;
  BoardController boardController;
};
