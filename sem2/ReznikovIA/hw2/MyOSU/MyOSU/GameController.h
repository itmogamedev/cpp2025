#pragma once

#include "GameModel.h";
#include "GameView.h";

class GameController {
 public:
  GameController(GameModel& model, GameView& view)
      : model(model), view(view) {};
  void run();
  void handleEvents();

  GameModel& model;
  GameView& view;
};
