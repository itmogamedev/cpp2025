#pragma once
#include <SFML/Graphics.hpp>

#include "GameModel.h"
#include "GameView.h"

class Game {
 public:
  Game();
  void run();

 private:
  void processEvents();
  void handleInput(float delta_time);
  void update(float delta_time);
  void render();

  float screen_width;
  float screen_height;

  sf::RenderWindow window;
  GameModel model;
  GameView view;
};
