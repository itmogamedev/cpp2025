#pragma once
#include <SFML/Graphics.hpp>

#include "game.h"

class engine {
 private:
  sf::RenderWindow appWindow;
  game gameObject;

  void processEvents();
  void updateGame();
  void renderGame();

 public:
  engine();
  void gameLoop();
};