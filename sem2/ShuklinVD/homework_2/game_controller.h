#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "game_model.h"
#include "view.h"

class GameController {
 private:
  GameModel model;
  View view;

 public:
  void handleEvents();
  void run();
};

#endif
