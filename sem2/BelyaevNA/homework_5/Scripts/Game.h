#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

#include "GameBoard.h"
#include "GameLogic.h"
#include "GameUI.h"

class Game {
 private:
  sf::RenderWindow window;
  sf::Font font;
  GameBoard board;
  GameLogic logic;
  GameUI ui;

  void handleInput();
  void update();
  void render();

 public:
  Game();
  void run();
};

#endif
