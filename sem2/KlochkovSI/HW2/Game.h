#ifndef GAME_H_
#define GAME_H_

#include <SFML/Graphics.hpp>

#include "GameController.h"
#include "GameModel.h"
#include "GameView.h"

class Game {
 public:
  Game();

  void run();

 private:
  sf::RenderWindow window_;
  sf::Clock clock_;

  GameModel model_;
  GameView view_;
  GameController controller_;
};

#endif  // GAME_H_
